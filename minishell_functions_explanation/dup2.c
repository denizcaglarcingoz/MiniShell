
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// // int dup2(int oldfd, int newfd);
// oldfd: The file descriptor that you want to duplicate.
// newfd: The desired file descriptor number for the duplicate.

int main() {
    int fd = open("example.txt", W_OK | O_CREAT | O_TRUNC);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Using dup2 to duplicate fd to file descriptor 10
    int new_fd = dup2(fd, STDOUT_FILENO);
	write(1, "Hello, world!\n", 14);
    // Both file descriptors can be used independently
    // ...

    close(fd); // Closing one of the descriptors does not close the other

    return 0;
}