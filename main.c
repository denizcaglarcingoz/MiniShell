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
#include <termios.h>

struct sigaction orig_sigquit_action;

void sigint_handler_int(int signum)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void sigint_handler_quit(int signum)
{
	write(1, "", 1);
}

int main()
{
    
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
	
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
		free(input);
    }
	
    return 0;
}

// cc main.c -o minishell -lreadline -lncurses