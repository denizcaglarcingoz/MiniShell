#include <stdio.h>
#include <unistd.h>

// The getcwd() function in C (standing for "get current working directory")
// is used to retrieve the absolute pathname of the current working directory.
// This function is part of the <unistd.h>
// header in Unix-like operating systems, including Linux.

int main() {
    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current Working Directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    return 0;
}