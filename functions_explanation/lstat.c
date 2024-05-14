#include <stdio.h>
#include <sys/stat.h>

//// lstat and stat are same with one twist.
/// lstat works directly on symbolic file
/// stat goes to work on where symbolic file directs to
//  if there is a symboliklink as the file

int main() {
    const char *filename = "symboliklinkchdir";
    struct stat fileStat;

    // Using lstat on a symbolic link
    if (lstat(filename, &fileStat) == 0) {
        printf("Size of symbolic link: %lld bytes\n", (long long)fileStat.st_size);
    } else {
        perror("lstat() error");
        return 1;
    }

    // Using stat on the same symbolic link
    if (stat(filename, &fileStat) == 0) {
        printf("Size of target file: %lld bytes\n", (long long)fileStat.st_size);
    } else {
        perror("stat() error");
        return 1;
    }

    return 0;
}

