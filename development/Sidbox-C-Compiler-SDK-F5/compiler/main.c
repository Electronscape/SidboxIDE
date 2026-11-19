#include "apis.h"
#include "apicore.h"
#include "compiler.h"

#include <stdio.h>
#include <string.h>

enum {
    PATH_CAPACITY = 256,
    BACKUP_RETAINED = -1,
    RESTORE_FAILED = -2,
    SOURCE_TOO_LARGE = -3,
    SOURCE_BINARY = -4
};

static char source_path[PATH_CAPACITY];
static char app_path[PATH_CAPACITY];
/* One shared pool. Multi-file builds have a combined 128 KiB source limit.
   Separate NUL terminators keep all file slices stable for compiler tokens. */
static char source[SIDC_SOURCE_LIMIT + SIDC_MAX_SOURCES];
static char input_paths[SIDC_MAX_SOURCES][PATH_CAPACITY];
static SidcSource input_sources[SIDC_MAX_SOURCES];
static unsigned input_count;
static char status[PATH_CAPACITY + 128];
static char stage_path[PATH_CAPACITY];
static char backup_path[PATH_CAPACITY];
static CGGadget editor;
static CGGadget save_button;
static CGGadget build_button;
static CGGadget status_label;

static const char starter[] =
    "extern int sidbox_message(const char *message);\n"
    "\n"
    "int main(void)\n"
    "{\n"
    "    sidbox_message(\"Hello from Sidbox!\");\n"
    "    return 0;\n"
    "}\n";

static void show_status(const char *text)
{
    if (status_label)
        SBOS_LabelSetText(status_label, text);
    else
        GUICoderGirl->console->printf(0, "%s\n", text);
}

/* Resolve a .c input or .app output against the shell working directory.
   Absolute and tfcard:/ paths are preserved verbatim. */
static int resolve_path(const char *input, const char *extension,
                        char *destination, unsigned capacity)
{
    if (!input || !*input)
        return 0;
    size_t length = strlen(input);
    size_t suffix = strlen(extension);
    if (length <= suffix)
        return 0;
    for (size_t i = 0; i < suffix; ++i) {
        unsigned char actual = (unsigned char)input[length - suffix + i];
        unsigned char expected = (unsigned char)extension[i];
        if ((actual | 32u) != (expected | 32u))
            return 0;
    }
    const char *drive = strchr(input, ':');
    int count;
    if (input[0] == '/' || (drive && drive[1] == '/')) {
        count = snprintf(destination, capacity, "%s", input);
    } else {
        if (drive)
            return 0;
        if (sfgetcwd(stage_path, sizeof(stage_path)) != FR_OK || stage_path[0] == 0)
            return 0;
        size_t cwd_length = strlen(stage_path);
        count = snprintf(destination, capacity, "%s%s%s", stage_path,
                         stage_path[cwd_length - 1] == '/' ? "" : "/", input);
    }
    return count > 0 && (unsigned)count < capacity;
}

/* Omitted -o preserves the existing first-source-names-the-app behaviour. */
static int set_paths(const char *input, const char *output)
{
    if (!resolve_path(input, ".c", source_path, sizeof(source_path)))
        return 0;
    if (output) {
        if (!resolve_path(output, ".app", app_path, sizeof(app_path)))
            return 0;
    } else {
        size_t count = strlen(source_path);
        /* Replace the last 'c' with 'app', keeping the dot. */
        if (count + 3u > sizeof(app_path))
            return 0;
        memcpy(app_path, source_path, count - 1u);
        memcpy(app_path + count - 1u, "app", sizeof("app"));
    }
    /* Both atomic-write filenames must fit the existing path buffers. */
    size_t count = strlen(app_path);
    return count + sizeof(".sidc-new") <= sizeof(stage_path) &&
           count + sizeof(".sidc-old") <= sizeof(backup_path);
}

static int read_file(const char *path, void *buffer, uint32_t capacity, uint32_t *length)
{
    const API_FILEIO *fs = SYSFileSystem;
    void *file;
    FRESULT result = fs->sbstream_open(path, SD_READ, &file);
    if (result != FR_OK)
        return result;

    uint32_t size = 0;
    uint32_t read = 0;
    int error = fs->sbstream_size(file, &size);
    if (error == FR_OK && size > capacity)
        error = SOURCE_TOO_LARGE;
    if (error == FR_OK && size != 0) {
        error = fs->sbstream_read(file, buffer, size, &read);
        if (error == FR_OK && read != size)
            error = FR_DISK_ERR;
    }
    result = fs->sbstream_close(file);
    if (error == FR_OK)
        error = result;
    if (error == FR_OK)
        *length = size;
    return error;
}

static int read_source(uint32_t *length)
{
    int result = read_file(source_path, source, SIDC_SOURCE_LIMIT, length);
    if (result != FR_OK)
        return result;
    if (memchr(source, 0, *length))
        return SOURCE_BINARY;
    source[*length] = '\0';
    return FR_OK;
}

static int read_sources(unsigned count, const char *const *paths)
{
    uint32_t used = 0;
    input_count = 0;
    for (unsigned i = 0; i < count; ++i) {
        unsigned index = input_count;
        if (!resolve_path(paths[i], ".c", input_paths[index], PATH_CAPACITY)) {
            snprintf(status, sizeof(status), "Invalid .c source path: %s", paths[i]);
            show_status(status);
            return 0;
        }
        uint32_t length = 0;
        char *destination = source + used + index;
        int result = read_file(input_paths[index], destination,
                               SIDC_SOURCE_LIMIT - used, &length);
        if (result != FR_OK) {
            if (result == SOURCE_TOO_LARGE)
                show_status("Combined sources exceed 128 KiB");
            else {
                snprintf(status, sizeof(status), "Open %s: file error %d",
                         input_paths[index], result);
                show_status(status);
            }
            return 0;
        }
        if (memchr(destination, 0, length)) {
            snprintf(status, sizeof(status), "Source contains NUL: %s", input_paths[index]);
            show_status(status);
            return 0;
        }
        destination[length] = '\0';
        input_sources[index] = (SidcSource){destination, length};
        used += length;
        ++input_count;
    }
    return 1;
}

/* Resolve quoted headers relative to the C file or header that includes them.
   A NULL buffer only resolves the name for the compiler's header cache. */
static int read_header(const char *including_path, const char *header_name,
                       char *buffer, uint32_t capacity, uint32_t *length,
                       char *resolved_path, uint32_t path_capacity)
{
    if (!including_path || !header_name || !*header_name ||
        header_name[0] == '/' || strchr(header_name, ':'))
        return 0;
    const char *slash = strrchr(including_path, '/');
    if (!slash)
        return 0;
    size_t prefix = (size_t)(slash - including_path) + 1u;
    size_t name_length = strlen(header_name);
    if (prefix + name_length >= path_capacity)
        return 0;
    memcpy(resolved_path, including_path, prefix);
    memcpy(resolved_path + prefix, header_name, name_length + 1u);
    if (!buffer)
        return 1;
    return read_file(resolved_path, buffer, capacity, length) == FR_OK;
}

static uint32_t read_apicore(void *buffer, uint32_t capacity)
{
    uint32_t length;
    return read_file(SIDC_APICORE_PATH, buffer, capacity, &length) == FR_OK ? length : 0;
}

static int write_file(char *path, const void *bytes, uint32_t length)
{
    const API_FILEIO *fs = SYSFileSystem;
    size_t path_length = strlen(path);
    if (path_length + sizeof(".sidc-new") > sizeof(stage_path) ||
        path_length + sizeof(".sidc-old") > sizeof(backup_path))
        return FR_DENIED;
    memcpy(stage_path, path, path_length);
    memcpy(stage_path + path_length, ".sidc-new", sizeof(".sidc-new"));
    memcpy(backup_path, path, path_length);
    memcpy(backup_path + path_length, ".sidc-old", sizeof(".sidc-old"));

    void *file;
    FRESULT result = fs->sbstream_open(stage_path, SD_WRITE | SD_CREATE_NEW, &file);
    if (result != FR_OK)
        return result;

    uint32_t written = 0;
    if (length != 0) {
        result = fs->sbstream_write(file, bytes, length, &written);
        if (result == FR_OK && written != length)
            result = FR_DISK_ERR;
    }
    if (result == FR_OK)
        result = fs->sbstream_flush(file);
    FRESULT close_result = fs->sbstream_close(file);
    if (result == FR_OK)
        result = close_result;
    if (result != FR_OK) {
        fs->sbremove(stage_path);
        return result;
    }

    uint32_t flags = 0;
    result = fs->sbstat(path, &flags, NULL);
    int saved_previous = 0;
    if (result == FR_OK) {
        /* sbstat uses CoderGirl directory-entry flags. Bit 0 is CG_DE_DIR. */
        result = (flags & 1u) ? FR_DENIED : fs->sbrename(path, backup_path);
        saved_previous = result == FR_OK;
    } else if (result == FR_NO_FILE) {
        result = FR_OK;
    }
    if (result == FR_OK)
        result = fs->sbrename(stage_path, path);
    if (result != FR_OK) {
        fs->sbremove(stage_path);
        if (saved_previous && fs->sbrename(backup_path, path) != FR_OK)
            return RESTORE_FAILED;
        return result;
    }
    if (saved_previous && fs->sbremove(backup_path) != FR_OK)
        return BACKUP_RETAINED;
    return FR_OK;
}

static int report_file(int result, const char *action)
{
    if (result == FR_OK)
        return 1;
    if (result == SOURCE_TOO_LARGE)
        show_status("Source exceeds 128 KiB");
    else if (result == SOURCE_BINARY)
        show_status("Source contains a NUL byte");
    else if (result == RESTORE_FAILED)
        show_status("Write failed. Previous file is in .sidc-old");
    else if (result == BACKUP_RETAINED)
        show_status("Write succeeded. Previous file is in .sidc-old");
    else {
        snprintf(status, sizeof(status), "%s failed (file error %d)", action, result);
        show_status(status);
    }
    return result == BACKUP_RETAINED;
}

static int build(uint32_t length)
{
    const void *app;
    SidcDiagnostic diagnostic;
    SidcSource one = {source, length};
    const char *paths[SIDC_MAX_SOURCES];
    for (unsigned i = 0; i < input_count; ++i)
        paths[i] = input_paths[i];
    const char *editor_path = source_path;
    uint32_t bytes = sidc_compile_project(input_count ? input_sources : &one,
                                          input_count ? paths : &editor_path,
                                          input_count ? input_count : 1u,
                                          read_apicore, read_header, &app, &diagnostic);
    if (bytes == 0) {
        const char *problem = diagnostic.path ? diagnostic.path
                            : diagnostic.file_index < input_count
                            ? input_paths[diagnostic.file_index] : source_path;
        const char *leaf = strrchr(problem, '/');
        snprintf(status, sizeof(status), "%s:%u:%u %s", leaf ? leaf + 1 : problem,
                 (unsigned)diagnostic.line, (unsigned)diagnostic.column,
                 diagnostic.message ? diagnostic.message : "Compilation failed");
        show_status(status);
        if (editor && !diagnostic.path && diagnostic.line && diagnostic.column) {
            SBOS_TextAreaSetCaret(editor, diagnostic.line - 1u, diagnostic.column - 1u);
            SBOS_GadgetSetFocus(editor);
        }
        return 0;
    }
    int result = write_file(app_path, app, bytes);
    if (result == FR_OK) {
        const char *leaf = status_label ? strrchr(app_path, '/') : NULL;
        if (input_count > 1u)
            snprintf(status, sizeof(status), "Built %s (%u bytes, %u sources)",
                     leaf ? leaf + 1 : app_path, (unsigned)bytes, input_count);
        else
            snprintf(status, sizeof(status), "Built %s (%u bytes)",
                     leaf ? leaf + 1 : app_path, (unsigned)bytes);
        show_status(status);
    }
    return report_file(result, "Build");
}

static CGWindowProcRes editor_proc(CGWindow win, const CGMessage_t *message)
{
    (void)win;
    if (!message || message->mtype != CGMSG_GADGET ||
        message->eventClass != CGEVT_GAD_ACTIVATED ||
        (message->gadget != save_button && message->gadget != build_button))
        return CGPROC_DEFAULT;

    uint32_t bytes = SBOS_TextAreaGetText(editor, source, SIDC_SOURCE_LIMIT + 1u);
    if (bytes == 0 || bytes > SIDC_SOURCE_LIMIT + 1u) {
        show_status("Source exceeds 128 KiB");
        return CGPROC_HANDLED;
    }
    if (message->gadget == build_button) {
        build(bytes - 1u);
    } else {
        int result = write_file(source_path, source, bytes - 1u);
        if (result == FR_OK)
            show_status("Source saved");
        else
            report_file(result, "Save");
    }
    return CGPROC_HANDLED;
}

static int open_editor(int new_file)
{
    CGWindow win = SBOS_CreateWindow(NULL, 12, 17, 456, 284, "Sidbox C",
        SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR | SBX_WF_MOVEABLE |
        SBX_WF_MINIMISE | SBX_WF_SCREENBOUND);
    if (win == 0xffu || win == 0u) {
        show_status("Could not open the C editor");
        return 1;
    }
    const char *leaf = strrchr(source_path, '/');
    CGGadget filename = SBOS_CreateLabel(win, 8, 9, 270, 16,
        leaf ? leaf + 1 : source_path, GAD_TOOL_DEFAULT);
    save_button = SBOS_CreateButton(win, 286, 4, 68, 24, "Save", GAD_TOOL_DEFAULT);
    build_button = SBOS_CreateButton(win, 360, 4, 78, 24, "Build", GAD_TOOL_DEFAULT);
    editor = SBOS_CreateTextArea(win, 8, 34, 430, 193, source, 0, GAD_TOOL_DEFAULT);
    status_label = SBOS_CreateLabel(win, 8, 235, 430, 18,
        new_file ? "New source file" : "Source loaded", GAD_TOOL_DEFAULT);
    if (!filename || !save_button || !build_button || !editor || !status_label) {
        SBOS_CloseWindow(win);
        status_label = 0;
        show_status("Could not create the C editor controls");
        return 1;
    }
    SBOS_SetWindowProc(win, editor_proc);
    SBOS_GadgetSetFocus(editor);
    return 0;
}

int main(int argc, char **argv)
{
    const char *sources[SIDC_MAX_SOURCES];
    const char *output = NULL;
    unsigned count = 0;
    int edit = argc == 1 || (argc == 3 && strcmp(argv[1], "-e") == 0);

    if (argc < 1 || (argc >= 2 && strcmp(argv[1], "-e") == 0 && !edit)) {
        show_status("Usage: compiler [-e file.c] | [-i] file.c [more.c ...] [-o name.app]");
        return 1;
    }
    if (!edit) {
        /* -i marks the input list; the original positional form also works.
           -o consumes exactly the next argument, which must end in .app. */
        int have_input_flag = 0;
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-i") == 0) {
                if (have_input_flag || i + 1 >= argc || argv[i + 1][0] == '-') {
                    show_status("Usage: compiler -i source.c [more.c ...] -o name.app");
                    return 1;
                }
                have_input_flag = 1;
            } else if (strcmp(argv[i], "-o") == 0) {
                if (output || i + 1 >= argc || argv[i + 1][0] == '-') {
                    show_status("Usage: compiler [-i] file.c [more.c ...] -o name.app");
                    return 1;
                }
                output = argv[++i];
            } else if (argv[i][0] == '-' || count >= SIDC_MAX_SOURCES) {
                show_status("Invalid option or too many sources (maximum 16)");
                return 1;
            } else {
                sources[count++] = argv[i];
            }
        }
        if (!count) {
            show_status("Usage: compiler [-i] file.c [more.c ...] [-o name.app]");
            return 1;
        }
    }

    const char *path = argc == 1 ? "hello.c" : edit ? argv[argc - 1] : sources[0];
    if (!set_paths(path, output)) {
        show_status("Choose valid .c sources and a .app output path (-o)");
        return 1;
    }

    if (!edit) {
        if (!read_sources(count, sources))
            return 1;
        return !build(0);
    }

    uint32_t length = 0;
    int result = read_source(&length);
    if (result == FR_NO_FILE) {
        memcpy(source, starter, sizeof(starter));
        return open_editor(1);
    }
    if (!report_file(result, "Open source"))
        return 1;
    return open_editor(0);
}
