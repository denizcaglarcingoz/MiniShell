#include "minishell.h"

void	free_envs(char **env, int i)
{
	if (env == NULL)
	{
		printf("Empty Environmental Variable List\n");
		return ;
	}
	int	j;

	j = -1;
	while (++j < i)
		free(env[j]);
	free(env);
}

void	free_all_env(char **env)
{
	if (env == NULL)
	{
		printf("Empty Environmental Variable List\n");
		return ;
	}
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	free_envs(env, i);
}

void	print_env(char **env)
{
	//int i;	

	//i = 0;
	if (env == NULL)
	{
		printf("Empty Environmental Variable List\n");
		return ;
	}
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

char	**get_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			j;

	i = 0;
	j = -1;
	if (environ == NULL || environ[i] == NULL)
		return (NULL);
	while (environ[i] != NULL)
		i++;
	env = (char **)malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (++j < i)
	{
		env[j] = ft_strdup(environ[j]);
		if (!env[j])
		{
			free_envs(env, j);
			return (NULL);
		}
	}
	env[i] = NULL;
	return (env);
}
