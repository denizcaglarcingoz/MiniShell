#include "minishell.h"


int	main(int ac, char **av)
{
	pid_t child_pid = fork(); // Create child process

	if (child_pid == 0) {
	    // Child process code
	    exit(5); // Exit with code 5
	} else {
	    // Parent process code
	    int status;
	    pid_t wait_result = waitpid(child_pid, &status, 0); // Wait for child

	    if (wait_result == child_pid) {
	        // Child process terminated successfully
	        if (WIFEXITED(status)) { // Check if child exited normally
	            int child_exit_code = WEXITSTATUS(status); // Extract exit code
	            printf("Child process exited with code: %d\n", child_exit_code);
	        } else {
	            // Handle abnormal child termination (e.g., signaled)
	            printf("Child process terminated abnormally\n");
	        }
	    } else {
	        // Handle waitpid error
	        perror("waitpid");
	    }
	}
}