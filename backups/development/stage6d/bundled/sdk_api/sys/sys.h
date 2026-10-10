#ifndef SYSTEMS_API_H
#define SYSTEMS_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	SD_READ				0x01
#define	SD_WRITE			0x02
#define	SD_OPEN_EXISTING	0x00
#define	SD_CREATE_NEW		0x04
#define	SD_CREATE_ALWAYS	0x08
#define	SD_OPEN_ALWAYS		0x10
#define	SD_OPEN_APPEND		0x30


typedef enum {
	FR_OK = 0,				/* (0) Succeeded */
	FR_DISK_ERR,			/* (1) A hard error occurred in the low level disk I/O layer */
	FR_INT_ERR,				/* (2) Assertion failed */
	FR_NOT_READY,			/* (3) The physical drive cannot work */
	FR_NO_FILE,				/* (4) Could not find the file */
	FR_NO_PATH,				/* (5) Could not find the path */
	FR_INVALID_NAME,		/* (6) The path name format is invalid */
	FR_DENIED,				/* (7) Access denied due to prohibited access or directory full */
	FR_EXIST,				/* (8) Access denied due to prohibited access */
	FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	FR_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
	FR_NOT_ENABLED,			/* (12) The volume has no work area */
	FR_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
	FR_MKFS_ABORTED,		/* (14) The f_mkfs() aborted due to any problem */
	FR_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
	FR_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	FR_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_LOCK */
	FR_INVALID_PARAMETER,	/* (19) Given parameter is invalid */
	FR_INVALIDFILENUMBER,	/* (20) Given filenumber is out of range */
} FRESULT;



typedef struct {
    FRESULT (*sbopen)     (uint8_t filenum, char *filename, uint8_t filemode);
    uint32_t (*sbfilelen) (uint8_t filenum);
    FRESULT (*sbread)     (uint8_t filename, void *buffer, uint32_t length, uint32_t *bytesread);
    FRESULT (*sbclose)    (uint8_t filenum);
    FRESULT (*sbwrite)    (uint8_t filenum, const void *buffer, uint32_t length, uint32_t *byteswritten);
    FRESULT (*sblseek)    (uint8_t filenum, uint32_t offset);
    FRESULT (*sbchdir)    (char *path);
    FRESULT (*sbgetcwd)   (char *buffer, uint32_t length);
    FRESULT (*sbcopy)     (char *source, char *dest);
    FRESULT (*sbmkdir)    (char *path);
    FRESULT (*sbstat)     (char *path, uint32_t *flags, uint32_t *size);
    void    *(*sbopendir) (char *path);
    int32_t (*sbreaddir)  (void *handle, char *name, uint32_t name_len, uint32_t *flags, uint32_t *size);
    void    (*sbclosedir) (void *handle);
} API_FILEIO;




typedef struct  {
    const API_FILEIO   *sys_fileio;
    void (*desktop_restore)(void);
    void (*desktop_suspend)(void);
} API_SYSTEMS;


#define SYSBase (API->system)
#define SYSFileSystem (SYSBase->sys_fileio)
// system defines
#define restore_desktop()                                  (SYSBase->desktop_restore())
#define suspend_desktop()                                  (SYSBase->desktop_suspend())



//#define suspect_desktop()                                  suspend_desktop()
#define sfopen(u8_filenum, s_filename, u8_filemode)       (SYSFileSystem->sbopen(u8_filenum, s_filename, u8_filemode))
#define sfread(u8_filenum, ptr_buffer, u32_len, u32_retb) (SYSFileSystem->sbread(u8_filenum, ptr_buffer, u32_len, u32_retb))
#define sfclose(u8_filenum)                               (SYSFileSystem->sbclose(u8_filenum))
#define sfwrite(u8_filenum, ptr_buffer, u32_len, u32_retb) (SYSFileSystem->sbwrite(u8_filenum, ptr_buffer, u32_len, u32_retb))
#define sflseek(u8_filenum, u32_offset)                   (SYSFileSystem->sblseek(u8_filenum, u32_offset))
#define sfchdir(s_path)                                   (SYSFileSystem->sbchdir(s_path))
#define sfgetcwd(ptr_buffer, u32_len)                     (SYSFileSystem->sbgetcwd(ptr_buffer, u32_len))
#define sfcopy(s_source, s_dest)                          (SYSFileSystem->sbcopy(s_source, s_dest))
#define sfmkdir(s_path)                                   (SYSFileSystem->sbmkdir(s_path))
#define sfstat(s_path, ptr_flags, ptr_size)               (SYSFileSystem->sbstat(s_path, ptr_flags, ptr_size))
#define sfopendir(s_path)                                 (SYSFileSystem->sbopendir(s_path))
#define sfreaddir(ptr_handle, ptr_name, u32_name_len, ptr_flags, ptr_size) \
    (SYSFileSystem->sbreaddir(ptr_handle, ptr_name, u32_name_len, ptr_flags, ptr_size))
#define sfclosedir(ptr_handle)                            (SYSFileSystem->sbclosedir(ptr_handle))








#ifdef __cplusplus
}
#endif

#endif
