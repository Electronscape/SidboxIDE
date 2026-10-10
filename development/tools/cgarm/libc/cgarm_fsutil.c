/* CGARM Phase 9: SBOS-backed directory, path and file management.
 * sbremove/sbrename require Phase 9 firmware; older Phase 7 file streams
 * remain unchanged. No host filesystem or native Newlib I/O is used.
 */
#ifndef SIDBOX_APPLET_V2
#error "CGARM Phase 9 source is for CGARM applets only"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "apis.h"

#define CGARM_DIR_MAGIC 0x43474439u

struct CGARM_DIR {
    uint32_t magic;
    void *os_handle;
    struct dirent entry;
};

static int fs_errno(FRESULT r)
{
    switch (r) {
    case FR_OK: return 0;
    case FR_NO_FILE: case FR_NO_PATH: return ENOENT;
    case FR_INVALID_NAME: case FR_INVALID_PARAMETER: return EINVAL;
    case FR_EXIST: return EEXIST;
    case FR_DENIED: case FR_WRITE_PROTECTED: return EACCES;
    case FR_TOO_MANY_OPEN_FILES: return EMFILE;
    case FR_NOT_READY: case FR_INVALID_DRIVE: return ENODEV;
    case FR_TIMEOUT: case FR_LOCKED: return EBUSY;
    default: return EIO;
    }
}

int remove(const char *path)
{
    if (!path || !*path) { errno = EINVAL; return -1; }
    FRESULT r = API->system->sys_fileio->sbremove(path);
    if (r != FR_OK) { errno = fs_errno(r); return -1; }
    return 0;
}

int rename(const char *old_path, const char *new_path)
{
    if (!old_path || !*old_path || !new_path || !*new_path) { errno = EINVAL; return -1; }
    FRESULT r = API->system->sys_fileio->sbrename(old_path, new_path);
    if (r != FR_OK) { errno = fs_errno(r); return -1; }
    return 0;
}

int mkdir(const char *path, mode_t mode)
{
    (void)mode; /* SBFS does not provide POSIX permissions. */
    if (!*path) { errno = EINVAL; return -1; }
    FRESULT r = API->system->sys_fileio->sbmkdir((char *)(void *)path);
    if (r != FR_OK) { errno = fs_errno(r); return -1; }
    return 0;
}

int chdir(const char *path)
{
    if (!*path) { errno = EINVAL; return -1; }
    FRESULT r = API->system->sys_fileio->sbchdir((char *)(void *)path);
    if (r != FR_OK) { errno = fs_errno(r); return -1; }
    return 0;
}

char *getcwd(char *buffer, size_t size)
{
    if (!buffer || size == 0 || size > UINT32_MAX) { errno = EINVAL; return NULL; }
    FRESULT r = API->system->sys_fileio->sbgetcwd(buffer, (uint32_t)size);
    if (r != FR_OK) { errno = fs_errno(r); return NULL; }
    return buffer;
}

DIR *opendir(const char *path)
{
    if (!path || !*path) { errno = EINVAL; return NULL; }
    DIR *dir = (DIR *)malloc(sizeof(*dir));
    if (!dir) { errno = ENOMEM; return NULL; }
    dir->os_handle = API->system->sys_fileio->sbopendir((char *)(void *)path);
    if (!dir->os_handle) { free(dir); errno = ENOENT; return NULL; }
    dir->magic = CGARM_DIR_MAGIC;
    return dir;
}

struct dirent *readdir(DIR *dir)
{
    if (!dir || dir->magic != CGARM_DIR_MAGIC || !dir->os_handle) {
        errno = EBADF; return NULL;
    }
    uint32_t flags = 0, bytes = 0;
    int32_t r = API->system->sys_fileio->sbreaddir(
        dir->os_handle, dir->entry.d_name, sizeof(dir->entry.d_name), &flags, &bytes);
    (void)bytes;
    if (r == 0) { errno = 0; return NULL; } /* End of directory */
    if (r < 0) { errno = EIO; return NULL; }
    dir->entry.d_ino = 0;
    dir->entry.d_type = (flags & 1u) ? DT_DIR : DT_REG; /* CG_DE_DIR = 1 */
    return &dir->entry;
}

int closedir(DIR *dir)
{
    if (!dir || dir->magic != CGARM_DIR_MAGIC || !dir->os_handle) {
        errno = EBADF; return -1;
    }
    API->system->sys_fileio->sbclosedir(dir->os_handle);
    dir->os_handle = NULL;
    dir->magic = 0;
    free(dir);
    return 0;
}
