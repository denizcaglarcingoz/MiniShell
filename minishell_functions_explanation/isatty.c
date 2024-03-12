// SYNOPSIS
//        #include <unistd.h>
//        int isatty(int fd);

// DESCRIPTION
//        The  isatty()  function tests whether fd is an open file descriptor re‐
//        ferring to a terminal.

// RETURN VALUE
//        isatty() returns 1 if fd is an open file descriptor referring to a ter‐
//        minal; otherwise 0 is returned, and errno is set to indicate the error.

// ERRORS
//        EBADF  fd is not a valid file descriptor.

//        ENOTTY fd  refers  to a file other than a terminal.  On some older ker‐
//               nels, some types of files resulted in the error EINVAL  in  this
//               case  (which  is a violation of POSIX, which specifies the error
//               ENOTTY).

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// in this case it will return 0 becuase what it opens is not interacting withh terminal like stdin or stdout

int main() {
    // Open a file or create one (replace "example.txt" with your file)
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//int fd = 12;
    // Check if the file descriptor is associated with a terminal
    if (isatty(fd)) {
        printf("File descriptor %d is associated with a terminal.\n", fd);
    } else {
        printf("File descriptor %d is not associated with a terminal.\n", fd);
    }
	printf("isattty return %d", isatty(fd));
    // Close the file descriptor
    close(fd);

    return 0;
}

// O_WRONLY: This flag indicates that the file should be opened for write-only access.

// O_CREAT: This flag is used to create the file if it does not exist.

// O_TRUNC: This flag is used to truncate the file to zero length if it already exists. If the file doesn't exist and O_CREAT is specified, this flag has no effect.

// 0644 is file permission mode. 