#include "minishell.h"

void ft_export(char **cmd)
{
	char	**env;
	int		i;

	env = get_full_env(0);
	if (cmd == NULL)
		return ;
	cmd++;
	while (*cmd)
	{
		int  k = 0;
		while ((*cmd)[k] && (*cmd)[k] != '=')
			k++;
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(env[i], *cmd, k - 1) == 0 && env[i][k] == '=')
			{
				free(env[i]);
				env[i] = ft_strdup(*cmd);
				break ;
			}
			i++;
		}
		cmd++;
	}
	if (*cmd == NULL)
	{	get_full_env(env);
		return ;
	}
	i = 0;
	while (env[i])
		i++;
	// env = ft_realloc(env, sizeof(char *) * (i + 2));
}