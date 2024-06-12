#include "minishell.h"


int	main(int ac, char **av)
{
	char *agv[] = {"/bin/echo", "", "", "", "", "", "-l", NULL};
	execve(agv[0], agv, NULL);
	return (0);
}