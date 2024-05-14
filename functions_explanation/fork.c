#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
 
//  The fork() function is used to create a new
//  process by duplicating the existing process. 
//  After the fork, you have two processes running concurrently:
//  the parent process and the child process.
//  The new process is an exact copy of the existing one,
//  including the code, data, and file descriptors.

int main() {
   
	int paren_pid = getpid();
   pid_t child_pid_1 = fork();
   pid_t child_pid_2 = fork();
	
	if(child_pid_1 == 0)
	{
		printf("child_pid_1 == 0\n");
		return (0);
	}
	if(child_pid_2 == 0)
	{
		printf("child_pid_2 == 0\n");
		return (0);
	}
		

    return 0;
}