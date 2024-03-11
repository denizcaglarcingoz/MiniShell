//  execve is a function that helps you run other executables
// It takes three arguments
//  one is path to the executable
// other one is variable inputs for the executable "argv" ending with null
// other one is environment variables



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *const args[] = {NULL};
    char *const env[] = {NULL}; // Empty environment for this example

    if (execve("/Users/denizcaglarcingoz/Desktop/CC/ft_printf/unlink", args, env) == -1)
    {
        perror("execve() error");
        return 1;
    }

    // This code will not be reached if execve is successful
    printf("This line will not be printed.\n");

    return 0;
}