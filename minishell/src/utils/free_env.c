#include "minishell.h"

void	free_env()
{
	char **env;
	int		i;

	env = get_full_env(0);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}