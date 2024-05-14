#include <stdio.h>
#include <string.h>
#include <errno.h>


// strerror:

// char *strerror(int errnum);

// The strerror function takes an error number as an argument and
// returns a pointer to a string describing the error.
// The error number is typically obtained from the errno variable.


// perror:

// void perror(const char *s);
// The perror function is used to print a description for the last error that occurred during a system call or library function.
// It takes a string s as an argument, which is typically a prefix or context information you want to include in the error message.
// It automatically appends the error description based on the current value of errno.


// strerror might be necessarry because you might want to check for other errors and write them out all together.

int main() {
    FILE *file = fopen("nonexistent_file.txt", "r");

    if (file == NULL) {
        perror("Error opening file\n");
        printf("\nError details: %s\n", strerror(errno));
        return 1;
    }

    // File handling code

    fclose(file);
    return 0;
}

