#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Here is the general form of the access function:

// c
// Copy code
// #include <unistd.h>

// int access(const char *path, int mode);
// path: The path of the file or directory whose accessibility is being checked.
// mode: The mode of access being checked. It can be a combination of the following flags:
// R_OK: Check read permission.
// W_OK: Check write permission.
// X_OK: Check execute permission.
// F_OK: Check if the file exists. 

int main() {
    const char *filename = "example.txt";

    // Check if the file is readable
    if (access(filename, R_OK) == 0) {
        printf("%s is readable.\n", filename);
    } else {
        perror("Error");
		printf("nabersin");
    }
	printf("naber");
    return 0;
}

