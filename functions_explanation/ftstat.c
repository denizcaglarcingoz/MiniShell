#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/// It is like stat but instead works on file descriptor files that are open
/// but sstill does the same shit to open files
///int fstat(int fd, struct stat *buf);

int main() {
    const char *filename = "example.txt";
    int fileDescriptor = open(filename, O_RDONLY);

    if (fileDescriptor == -1) {
        perror("open() error");
        return 1;
    }

    struct stat fileStat;

    if (fstat(fileDescriptor, &fileStat) == 0) {
        printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
        printf("Last Access Time: %s", ctime(&fileStat.st_atime));
        // Additional information can be extracted from fileStat structure
    } else {
        perror("fstat() error");
        return 1;
    }

    close(fileDescriptor);

    return 0;
}

