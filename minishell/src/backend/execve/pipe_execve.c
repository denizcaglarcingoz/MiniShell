
#include "minishell.h"


char	**pipe_append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	while(str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char*));	
	if (new == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while(str[i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		i++;
	}
	new[i] = NULL;
	free(path_add);
	return (new);
}

char	*pipe_path_run(char **all_paths, char **argv, char **environ, int is_out)
{
	int		i;
	i = 0;
	
	if (is_out == 2)
	{return (NULL);}
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0)
		{	
			if (execve(all_paths[i], argv, environ) == -1)
			free_d_str(all_paths);
			printf("execve failed\n");
			exit(0);
		}
		i++;
	}
	free_d_str(all_paths);
	return (NULL);
}
char	*ft_pipe_execve(char *path, char **argv, int is_out)
{
	char	**environ;
	char	**all_paths;
	char	**paths;

	environ = get_full_env(0);
	if (argv[0] == NULL)
		return (NULL);
	if (access(path, X_OK) == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			return (NULL);
		}
		exit(0);
	}
	paths = ft_split(get_env("PATH"), ':');
	all_paths = pipe_append_path(paths, ft_strjoin("/", path));
	free_d_str(paths);
	if (all_paths == NULL)
		return (NULL);
	return (pipe_path_run(all_paths, argv, environ, is_out));
}

