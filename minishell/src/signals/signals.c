#include "minishell.h"

void sigint_handler_int(int signum)
{
	(void)signum;/// use for...
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

// void sigint_handler_quit(int signum)
// {
// 	(void)signum;///use for...
// 	write(1, " ", 1);
// 	exit(0);
// }