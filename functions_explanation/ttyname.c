// NAME
//        ttyname, ttyname_r - return name of a terminal

// SYNOPSIS
//        #include <unistd.h>

//        char *ttyname(int fd);

//        int ttyname_r(int fd, char *buf, size_t buflen);

// DESCRIPTION
//        The  function  ttyname() returns a pointer to the null-terminated pathname of the terminal de‐
//        vice that is open on the file descriptor fd, or NULL on error (for example, if fd is not  con‐
//        nected to a terminal).  The return value may point to static data, possibly overwritten by the
//        next call.  The function ttyname_r() stores this pathname in the buffer buf of length buflen.

// RETURN VALUE
//        The function ttyname() returns a pointer to a pathname on success.   On  error,  NULL  is  re‐
//        turned, and errno is set appropriately.  The function ttyname_r() returns 0 on success, and an
//        error number upon error.

// ERRORS
//        EBADF  Bad file descriptor.

//        ENODEV fd refers to a slave pseudoterminal device but the corresponding pathname could not  be
//               found (see NOTES).

//        ENOTTY fd does not refer to a terminal device.

//        ERANGE (ttyname_r()) buflen was too small to allow storing the pathname.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

int main() {
    // Get the name of the terminal associated with standard input
    char *terminal_name_stdin = ttyname(fileno(stdin));
	
	int fd = open("example.txt", 0);
	char *ttynames = ttyname(fd);
	printf("opening 'example.txt' and its tttyname: %s\n", ttynames);

    if (terminal_name_stdin != NULL) {
        printf("Terminal name for stdin: %s\n", terminal_name_stdin);
    } else {
        perror("ttyname for stdin");
    }

    // Get the name of the terminal associated with standard output
    char *terminal_name_stdout = ttyname(fileno(stdout));

    if (terminal_name_stdout != NULL) {
        printf("Terminal name for stdout: %s\n", terminal_name_stdout);
    } else {
        perror("ttyname for stdout");
    }

    return 0;
}
// they both return same name because they are both connected to same terminal


