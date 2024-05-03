#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"


char	**append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char*));	
	if (new == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		i++;
	}
	new[i] = NULL;
	free(path_add);
	free_d_str(str);
	return (new);
}

void	path_run(char **all_paths, char **argv, char **environ, t_table *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0)
		{
			if ((pid = fork()) == -1)
				return (free_all(table, 1, "fork fail"));
			if (pid == 0)	
			{
				execve(all_paths[i], argv, environ);
				free_d_str(all_paths);
				free_all(table, 1, "execve failed\n");
			}
			else
			{
				wait(NULL);
				free_d_str(all_paths);
				return ;
			}
		}
		i++;
	}
	write(2, argv[0], ft_strlen(argv[0]));
	if (ft_strlen(argv[0]) > 0)
		write(2, ": command not found\n", 20);
	free_d_str(all_paths);
}

void	ft_execve(t_table *table)
{
	char	**environ;
	char	**all_paths;
	pid_t	pid;

	environ = get_full_env(0);
	if (table->args[0] == NULL)
		return ;
	if (access(table->args[0], X_OK) == 0)
	{
		if ((pid = fork()) == -1)
			return (free_all(table, 1, "fork fail"));
		if (pid == 0)	
		{
			execve(table->args[0], table->args, environ);
			free_all(table, 1,("execve failed\n"));
		}
		else
		{	
			wait(NULL);
			return ;
		}
	}
	all_paths = append_path(ft_split(get_env("PATH"), ':'), ft_strjoin("/", table->args[0]));
	if (all_paths == NULL)
		free_all(table, 1, "Malloc Error\n");
	path_run(all_paths, table->args, environ, table);
}
