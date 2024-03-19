
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <executable> [arguments]\n", argv[0]);
        return 1;
    }

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        return 1;
    }
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    close(input_fd);
    if (execvp(argv[2], &argv[2]) == -1) {
        perror("execvp");
        return 1;
    }

    return 0;
}
