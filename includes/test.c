#include "minishell.h"


int	main(int ac, char **av)
{
	char **agv;
	agv = (char **)malloc(4 * sizeof(char));
	agv[0] = (char*)malloc(9 * sizeof(char));
	agv[0] = "/bin/cat";

	agv[1] = (char*)malloc(4 * sizeof(char));
	agv[1][0] = 'x';
	agv[1][1] = 'b';
	agv[1][2] = 'x';

	agv[2] = (char*)malloc(1 * sizeof(char));
	agv[2] = "";

	agv[3] = NULL;

	printf("agv[0]: %s\n", agv[0]);
	printf("agv[1]: %s\n", agv[1]);
	execve(agv[0], agv, NULL);
	return (0);
}