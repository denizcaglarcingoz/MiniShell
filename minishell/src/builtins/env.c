#include "minishell.h"

void ft_env()
{
	char	**env;
	int		i;

	i = 0;
	env = get_full_env(0);
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}