#include "minishell.h"

static char	**ft_allocate(char **path_names, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	path_names = (char **)malloc((i + 1) * sizeof(char *));
	if (!path_names)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][++j] != '=')
			j++;
		path_names[i] = (char *)malloc((j + 1) * sizeof(char));
		if (!path_names[i])
		{
			free_envs(path_names, i);
			return (NULL);
		}
	}
	return (path_names);
}

static char	**fill_path_names_env(char **path_names, char **env)
{
	int	i;
	int	j;

	path_names = ft_allocate(path_names, env);
	if (!path_names)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j] != '=')
		{
			path_names[i][j] = env[i][j];
		}
		path_names[i][j] = '\0';
	}
	path_names[i] = NULL;
	return (path_names);
}

char	*ft_getenv(char *path, char **env)
{
	int		i;
	char	**path_names;
	size_t	path_len;

	if (path == NULL || *path == '\0')
	{
		printf("No path specified\n");
		return (NULL);
	}
	path_names = NULL;
	path_names = fill_path_names_env(path_names, env);
	if (!path_names)
		return (NULL);
	i = 0;
	while (ft_strcmp(path_names[i], path) != 0)
		i++;
	path_len = ft_strlen(path);
	free_all_env(path_names);
	if (!env[i])
		return (NULL);
	return (env[i] + path_len + 1);
}
