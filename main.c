#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <termcap.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h> 

void sigint_handler(int signum)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

int main()
{
    

	signal(SIGINT, sigint_handler);

	while (1)
	{
        char* input = readline("MINISHELL> ");
		if (errno != 0 )
		{
			perror("Malloc Error");
			clear_history();
			break;
		}
		if (input == 0)
		{
			clear_history();
			break;
		}
        if(strcmp(input, "") != 0)
		{
			add_history(input);
		}
        if (strcmp(input, "exit") == 0) {
            printf("Exiting MINISHELL!\n");
            free(input);
            break;
        }
    }

    return 0;
}