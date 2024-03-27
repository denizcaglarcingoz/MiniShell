#include "minishell.h"

/// remember to add/delete variabes if they run the commands
// like this variable = "DENIZ=deniz/home/cd asdasdadasdasdDasdasd"

static char	**add_env_helper(char **env, char **new_env, \
	char *variable, int size)
{
	int	i;

	i = -1;
	new_env = (char **)malloc((size + 2) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (++i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_envs(new_env, i);
			return (NULL);
		}
	}
	new_env[i] = ft_strdup(variable);
	if (!new_env[i])
	{
		free_envs(new_env, i);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**add_env(char **env, char *variable)
{
	int		i;
	char	**new_env;

	i = 0;
	if (variable == NULL || *variable == '\0')
		return (env);
	new_env = NULL;
	while (env[i] != NULL)
		i++;
	new_env = add_env_helper(env, new_env, variable, i);
	if (!new_env)
		return (NULL);
	free_envs(env, i);
	return (new_env);
}

static char	**del_env_helper(char **env, char **new_env, \
	char *variable, int size)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	new_env = (char **)malloc((size) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (++i < size)
	{
		if (ft_strcmp(env[i], variable) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				free_envs(new_env, j);
				return (NULL);
			}
		}
		j++;
	}
	new_env[j - 1] = NULL;
	return (new_env);
}

char	**del_env(char **env, char *variable)
{
	int		i;
	char	**new_env;

	i = 0;
	if (variable == NULL || *variable == '\0')
		return (env);
	new_env = NULL;
	while (env[i] != NULL)
		i++;
	new_env = del_env_helper(env, new_env, variable, i);
	if (!new_env)
		return (NULL);
	free_envs(env, i);
	return (new_env);
}
