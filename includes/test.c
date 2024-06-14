#include "minishell.h"


int	main(int ac, char **av)
{
	char *axv[] = {"/bin/cat", "\"-l\"", NULL};

	execve("/bin/ls", axv, NULL);
}