#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int pipefd[2];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
		close(pipefd[1]);  // Close the write end since child is reading

		int sum = 0;
		int number;

		// Read numbers from the pipe and calculate their sum
		while (read(pipefd[0], &number, sizeof(int)) > 0)
		{ 
			sum += number;
		}

		printf("Child process: Sum = %d\n", sum);

		close(pipefd[0]);  // Close the read end after reading
	} else { // Parent process
		close(pipefd[0]);  // Close the read end since parent is writing

		// Generate and send numbers to the pipe
		for (int i = 1; i <= 3; ++i) {
			write(pipefd[1], &i, sizeof(int));
		}

		close(pipefd[1]);  // Close the write end after writing
	}

	return 0;
}