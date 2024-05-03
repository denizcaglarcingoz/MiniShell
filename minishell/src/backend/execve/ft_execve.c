#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"


void	pipe_init_exec(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		{
    		perror("Pipe creation failed");
			//free_table(exp_table);
    		exit(EXIT_FAILURE);
		}
}

char	**append_path(char **str, char *path_add)
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
	free_d_str(str);
	return (new);
}

char	*path_run(char **all_paths, char **argv, char **environ)
{
	int		i;
	pid_t	pid;
	i = 0;
	
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0)
		{
			if ((pid = fork()) == -1)
				return ("fork failed\n");
			if (pid == 0)	
			{
				execve(all_paths[i], argv, environ);
				free_d_str(all_paths);
				// free tables
				perror("execve failed\n");
				exit(127);
			}
			else
			{
				wait(NULL);
				free_d_str(all_paths);
				return (NULL) ;
			}
		}
		i++;
	}
	write(2, argv[0], ft_strlen(argv[0]));
	if (ft_strlen(argv[0]) > 0)
		write(2, "command not found\n", 18);
	free_d_str(all_paths);
	return (NULL);
}

char	*ft_execve(char *path, char **argv, t_shell *shell)//shell
{
	//char	**environ;
	char		**all_paths;
	pid_t	pid;

	//environ = get_full_env(0);
	if (argv[0] == NULL)
		return (NULL);
	if (access(path, X_OK) == 0)
	{
		if ((pid = fork()) == -1)
			return (perror("execve failed\n"), "fork failed\n");
		if (pid == 0)	
		{
			execve(path, argv, shell->env);
			return (perror("execve failed\n"), "fork failed\n");
		}
		else
			return (wait(NULL), NULL);
	}
	all_paths = append_path(ft_split(getenv("PATH"), ':'), ft_strjoin("/", path));//changed get_env to getenv
	if (all_paths == NULL)
		return ("malloc failed\n");
	return (path_run(all_paths, argv, shell->env));
}
