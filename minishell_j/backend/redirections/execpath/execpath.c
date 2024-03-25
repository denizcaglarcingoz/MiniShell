#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "/home/dcingoz/CC/minishell/minishell_j/headers/minishell.h"

void	free_d_str(char **str)
{
	int	i;

	i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;	
	}
	free(str);
}

char	**append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	while(str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char*));	
	if (new == NULL)Z
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
	free_d_str(str);
	return (new);
}

int path_run(char **all_paths, char **argv, char **environ)
{
	int i;
	
	i = 0;
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0)
		{
			if (execve(all_paths[i], ++argv, environ) == -1)
			{
				perror("execve");
				free_d_str(all_paths);
				return (1);
			}
			free_d_str(all_paths);
			return (0);
		}
		i++;
	}
	free_d_str(all_paths);
	return (0);
}

int	exter_cmd_run(char *path, char **argv)
{
	extern char	**environ;
	char		**all_paths;

	if (path == NULL)
		return (1);
	if (access(path, X_OK) == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			return (1);
		}
		return (0);
	}
	all_paths = append_path(ft_split(getenv("PATH"), ':'), ft_strjoin("/", path));
	if (all_paths == NULL)
		return (1);
	if (path_run(all_paths, argv, environ) == 1)
		return (1);
	return (0);
}

// TEST

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Not enough arg\n");
		return (1);
	}
	exter_cmd_run(argv[1], argv);
	return (0);
}


