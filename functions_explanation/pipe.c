#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>

// The pipe function in C is used to create an interprocess 
// communication (IPC) channel between two related processes. 
// It allows one process to send data to another process. 
// The pipe system call is commonly used in conjunction with 
// the fork system call to establish communication between a parent and a child process.


// The pipefd parameter is an array of two integers that will be filled in by the function.
// pipefd[0] is the file descriptor for the read end of the pipe,
// and pipefd[1] is the file descriptor for the write end of the pipe.


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