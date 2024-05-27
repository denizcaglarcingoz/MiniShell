#include "minishell.h"

extern pid_t sig_int;

void sigint_handler_int(int signum)
{	
	(void)signum;/// use for...
	if (sig_int != getpid() && kill(sig_int, SIGUSR1) == 0)
		return ;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
}
void	sigint_handler_hdoc(int signum)
{
	(void)signum;/// use for...
	if (sig_int != 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	sig_int = 1;
	return;
}
void	sigint_handler_child(int signum)
{
	(void)signum;/// use for...
	return;
}