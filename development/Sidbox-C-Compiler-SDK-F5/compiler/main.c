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
static char source[SIDC_SOURCE_LIMIT + 1u];
static char status[PATH_CAPACITY + 64];
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

static int set_paths(const char *input)
{
    size_t length = strlen(input);
    if (length < 3 || input[length - 2] != '.' || (input[length - 1] | 32) != 'c')
        return 0;
    const char *drive = strchr(input, ':');
    int count;
    if (input[0] == '/' || (drive && drive[1] == '/')) {
        count = snprintf(source_path, sizeof(source_path), "%s", input);
    } else {
        if (drive)
            return 0;
        if (sfgetcwd(stage_path, sizeof(stage_path)) != FR_OK || stage_path[0] == 0)
            return 0;
        size_t cwd_length = strlen(stage_path);
        count = snprintf(source_path, sizeof(source_path), "%s%s%s", stage_path,
                         stage_path[cwd_length - 1] == '/' ? "" : "/", input);
    }
    /* Allow for replacing .c with .app and temporary-file suffixes. */
    if (count < 3 || (unsigned)count + sizeof(".app.sidc-new") >= sizeof(source_path))
        return 0;
    memcpy(app_path, source_path, (size_t)count - 1u);
    memcpy(app_path + count - 1, "app", sizeof("app"));
    return 1;
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

static uint32_t read_apicore(void *buffer, uint32_t capacity)
{
    uint32_t length;
    return read_file(SIDC_APICORE_PATH, buffer, capacity, &length) == FR_OK ? length : 0;
}

static int write_file(char *path, const void *bytes, uint32_t length)
{
    const API_FILEIO *fs = SYSFileSystem;
    snprintf(stage_path, sizeof(stage_path), "%s.sidc-new", path);
    snprintf(backup_path, sizeof(backup_path), "%s.sidc-old", path);

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
        show_status("Source exceeds 8 KiB");
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
    uint32_t bytes = sidc_compile(source, length, read_apicore, &app, &diagnostic);
    if (bytes == 0) {
        snprintf(status, sizeof(status), "%u:%u  %s", (unsigned)diagnostic.line,
                 (unsigned)diagnostic.column, diagnostic.message);
        show_status(status);
        if (editor && diagnostic.line && diagnostic.column) {
            SBOS_TextAreaSetCaret(editor, diagnostic.line - 1u, diagnostic.column - 1u);
            SBOS_GadgetSetFocus(editor);
        }
        return 0;
    }
    int result = write_file(app_path, app, bytes);
    if (result == FR_OK) {
        const char *leaf = status_label ? strrchr(app_path, '/') : NULL;
        snprintf(status, sizeof(status), "Built %s (%u bytes)", leaf ? leaf + 1 : app_path,
                 (unsigned)bytes);
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

    uint32_t bytes = SBOS_TextAreaGetText(editor, source, sizeof(source));
    if (bytes == 0 || bytes > sizeof(source)) {
        show_status("Source exceeds 8 KiB");
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
    int edit = argc == 1 || (argc == 3 && strcmp(argv[1], "-e") == 0);
    if (argc != 1 && argc != 2 && !edit) {
        show_status("Usage: launch compiler.app [-e] source.c");
        return 1;
    }
    const char *path = argc == 1 ? "hello.c" : argv[argc - 1];
    if (!set_paths(path)) {
        show_status("Choose a .c source path");
        return 1;
    }

    uint32_t length = 0;
    int result = read_source(&length);
    if (edit && result == FR_NO_FILE) {
        memcpy(source, starter, sizeof(starter));
        return open_editor(1);
    }
    if (!report_file(result, "Open source"))
        return 1;
    return edit ? open_editor(0) : !build(length);
}
