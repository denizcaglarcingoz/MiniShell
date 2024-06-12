#include "minishell.h"


int	main(int ac, char **av)
{
	write(2, av[1], 14);
	return (0);
}