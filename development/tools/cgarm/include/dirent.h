/* CGARM Phase 9: lightweight directory API backed by SBOS. */
#ifndef CGARM_DIRENT_H
#define CGARM_DIRENT_H
#ifdef __cplusplus
extern "C" {
#endif
#define DT_UNKNOWN 0
#define DT_DIR 4
#define DT_REG 8
struct dirent {
    unsigned long d_ino;
    unsigned char d_type;
    char d_name[256];
};
typedef struct CGARM_DIR DIR;
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
#ifdef __cplusplus
}
#endif
#endif
