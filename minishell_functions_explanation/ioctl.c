
// NAME
//        ioctl - control device

// SYNOPSIS
//        #include <sys/ioctl.h>

//        int ioctl(int fd, unsigned long request, ...);

// DESCRIPTION
//        The  ioctl()  system  call  manipulates the underlying device parameters of special files.  In
//        particular, many operating characteristics of character special files (e.g., terminals) may be
//        controlled with ioctl() requests.  The argument fd must be an open file descriptor.

//        The  second  argument  is  a  device-dependent request code.  The third argument is an untyped
//        pointer to memory.  It's traditionally char *argp (from the days before void * was  valid  C),
//        and will be so named for this discussion.

//        An ioctl() request has encoded in it whether the argument is an in parameter or out parameter,
//        and the size of the argument argp in bytes.  Macros and defines used in specifying an  ioctl()
//        request are located in the file <sys/ioctl.h>.  See NOTES.
// RETURN VALUE
//        Usually,  on success zero is returned.  A few ioctl() requests use the return value as an out‐
//        put parameter and return a nonnegative value on success.  On error, -1 is returned, and  errno
//        is set appropriately.


// control function, it is used to get info about terminal input output etc.
// did not totalyl



// #include <stdio.h>
// #include <sys/ioctl.h>
// #include <unistd.h>

// int main() {
//     struct winsize ws;

//     // Get the terminal size using ioctl
//     if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
//         perror("ioctl");
//         return 1;
//     }

//     // Print the terminal size
//     printf("Terminal width: %d, height: %d\n", ws.ws_col, ws.ws_row);

    
// }

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main()
{

    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
        return 1;
    }

    // Print the terminal size
    printf("Terminal width: %d, height: %d\n", ws.ws_col, ws.ws_row);

    // Set new baud rate using ioctl
    int fd = STDOUT_FILENO;  // Use STDOUT_FILENO for standard output, change it as needed
    speed_t new_baud_rate = B9600;  // Replace with desired baud rate

    if (ioctl(fd, TIOCGSERIAL, &new_baud_rate) == -1) {
        perror("ioctl TIOCGSERIAL");
        return 1;
    }

    printf("Baud rate set to %lu\n", (unsigned long)new_baud_rate);

    // Your additional code here...

    return 0;
}