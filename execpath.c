#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(stderr, "Usage: %s <executable> [arguments]\n", argv[0]);
        return 1;
    }
    extern char **environ;
    if (execve(argv[1], &argv[1], environ) == -1) {
        perror("execve");
        return 1;
    }
    return 0;
}