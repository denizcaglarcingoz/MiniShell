
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>

// The stat function in C is used to retrieve information about a file or
// a file system object (like a directory). It provides details such as file size,
// permissions, modification time, and more. 

// The function is part of the <sys/stat.h> header file.

// Here's the general syntax for the stat function:
// int stat(const char *path, struct stat *buf);

// path: A string representing the path to the file or directory for which you want to retrieve information.
// buf: A pointer to a struct stat where the information about the file or directory will be stored.

// Here's an example of using stat:


int main() {
    const char *filename = "example.txt";
    struct stat fileStat;

    if (stat(filename, &fileStat) == 0) {
        printf("File Size: %ld bytes\n", (long)fileStat.st_size);
        printf("Last Access Time: %s", ctime(&fileStat.st_atime));
        // Additional information can be extracted from fileStat structure
    } else {
        perror("stat() error");
        return 1;
    }
    

    return 0;
}

// inside of struct stat:q
//  struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is defined */
//          dev_t           st_dev;           /* ID of device containing file */
//          mode_t          st_mode;          /* Mode of file (see below) */
//          nlink_t         st_nlink;         /* Number of hard links */
//          ino_t           st_ino;           /* File serial number */
//          uid_t           st_uid;           /* User ID of the file */
//          gid_t           st_gid;           /* Group ID of the file */
//          dev_t           st_rdev;          /* Device ID */
//          struct timespec st_atimespec;     /* time of last access */
//          struct timespec st_mtimespec;     /* time of last data modification */
//          struct timespec st_ctimespec;     /* time of last status change */
//          struct timespec st_birthtimespec; /* time of file creation(birth) */
//          off_t           st_size;          /* file size, in bytes */
//          blkcnt_t        st_blocks;        /* blocks allocated for file */
//          blksize_t       st_blksize;       /* optimal blocksize for I/O */
//          uint32_t        st_flags;         /* user defined flags for file */
//          uint32_t        st_gen;           /* file generation number */
//          int32_t         st_lspare;        /* RESERVED: DO NOT USE! */
//          int64_t         st_qspare[2];     /* RESERVED: DO NOT USE! */
//      };

//  The time-related fields of struct stat are as follows:
//  st_atime         Time when file data last accessed.  Changed by the mknod(2), utimes(2) and read(2) system calls.
//  st_mtime         Time when file data last modified.  Changed by the mknod(2), utimes(2) and write(2) system calls.
//  st_ctime         Time when file status was last changed (inode data modification).  Changed by the chmod(2), chown(2), link(2), mknod(2), rename(2), unlink(2), utimes(2) and write(2) system calls.
//  st_birthtime     Time of file creation.  Only set once when the file is created.  This field is only available in the 64 bit inode variants.  On filesystems where birthtime is not available, this field is
//                   set to 0 (i.e. epoch).
//  The size-related fields of the structures are as follows:
//  st_blksize     The optimal I/O block size for the file.
//  st_blocks      The actual number of blocks allocated for the file in 512-byte units.  As short symbolic links are stored in the inode, this number may be zero.

//  The status information word st_mode has the following bits:
//  #define S_IFMT 0170000           /* type of file */
//  #define        S_IFIFO  0010000  /* named pipe (fifo) */
//  #define        S_IFCHR  0020000  /* character special */
//  #define        S_IFDIR  0040000  /* directory */
//  #define        S_IFBLK  0060000  /* block special */
//  #define        S_IFREG  0100000  /* regular */
//  #define        S_IFLNK  0120000  /* symbolic link */
//  #define        S_IFSOCK 0140000  /* socket */
//  #define        S_IFWHT  0160000  /* whiteout */
//  #define S_ISUID 0004000  /* set user id on execution */
//  #define S_ISGID 0002000  /* set group id on execution */
//  #define S_ISVTX 0001000  /* save swapped text even after use */
//  #define S_IRUSR 0000400  /* read permission, owner */
//  #define S_IWUSR 0000200  /* write permission, owner */
//  #define S_IXUSR 0000100  /* execute/search permission, owner */
//  For a list of access modes, see ⟨sys/stat.h⟩, access(2) and chmod(2).