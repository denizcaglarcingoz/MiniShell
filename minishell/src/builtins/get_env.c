#include "minishell.h"

char	**free_env(char **env, int i)
{
	while (i >= 0)
	{
		free(env[i]);
		i--;
	}
	free(env);
	return (0);
}

char	**ft_d_strdup(char **env)
{
	int i;
	char **new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (0);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_env(new_env, i - 1));
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

char	**get_full_env(char **new_env)
{
	static char **env = 0;
	if (new_env)
		env = new_env;
	return env;
}

char	*get_env(char *key)
{
	char	**env;
	char	*value;
	int		i;
	int		j;

	env = get_full_env(0);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], key, j) == 0 && key[j] == 0)
		{
			value = ft_strdup(env[i] + j + 1);
			if (!value)
				return (0);
			return (value);
		}
		i++;
	}
	return (0);
}