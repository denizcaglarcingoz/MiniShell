#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The unlink function is a system call in Unix-like operating systems
// that is used to delete a specified file or, more precisely, to remove a directory entry.
// The removal of the file or directory entry depends on the file's link count.

// int unlink(const char *pathname);


int main() {
    const char *filename = "/Users/denizcaglarcingoz/Desktop/CC/chdir/deneme copy.c";

    if (unlink(filename) == 0) {
        printf("File %s unlinked successfully.\n", filename);
    } else {
        perror("unlink() error");
        return 1;
    }

    return 0;
}