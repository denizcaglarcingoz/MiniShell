#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main() {
    const char* targetDirectory = "/Users/denizcaglarcingoz/Desktop/CC/chdir";

    // Change the current working directory
    if (chdir(targetDirectory) == 0) {
        printf("\n\nChanged directory to: %s\n", targetDirectory);

        // List files in the current directory
        DIR* dir;
        struct dirent* entry;

        if ((dir = opendir(".")) != NULL) {
            printf("Files in the directory:\n");
            entry = readdir(dir);
            printf("%s\n", entry->d_name);
            entry = readdir(dir);
            printf("%s\n", entry->d_name);
            closedir(dir);

            // Perform file operations in the target directory
            // ...

        } else {
            perror("opendir() error");
            return 1;
        }

    } else {
        perror("chdir() error");
        return 1;
    }

    return 0;
}