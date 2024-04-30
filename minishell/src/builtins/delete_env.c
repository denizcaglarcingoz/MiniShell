#include "minishell.h"
//works now, possible double free somewhere.. here or add?

static int	compare_names(char *name, char *var)
{
	while (*name != '=' && *var && (*name == *var))
	{
		name++;
		var++;
	}
	if (*name == '=' && *var == '\0')
		return (0);
	else
		return (*name - *var);
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
		if (compare_names(env[i], variable) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				free_envs(new_env, j);
				return (NULL);
			}
		j++;
		}
	}
	new_env[j] = NULL;
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
