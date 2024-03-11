#include <stdio.h>
#include <dirent.h>

// opendir("path")
// opens the path directory


// readdir(DIR *directory)
// reads the info about the open directory
// //d_name: The name of the directory entry (file or subdirectory).
// d_ino: The inode number (a unique identifier) of the entry.
// d_type: The type of the entry (regular file, directory, symbolic link, etc.).

// closedir(DIR *directory)
// closes the open directory


int main() {
    DIR *directory = opendir("./example_directory");
    
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("Entry: %s\n", entry->d_name);
    }

    closedir(directory);
    return 0;
}