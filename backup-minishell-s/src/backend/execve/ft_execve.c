#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"

extern pid_t sig_int;

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
		//clean;
		i++;
	}
	new[i] = NULL;
	free(path_add);
	free_d_str(str);
	return (new);
}

char	*path_run(char **all_paths, char **argv, char **environ, t_shell *shell)
{
	int		i;
	pid_t	pid;
	i = 0;
	
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0)
		{
			if ((pid = fork()) == -1)
			{
				free_d_str(all_paths);
				free_all(shell, "execve fail\n", 127);
			}
			if (pid == 0)	
			{
				
				execve(all_paths[i], argv, environ);
				free_d_str(all_paths);
				free_all(shell, "execve fail\n", 127);
			}
			else
			{
				
				wait(NULL);
				free_d_str(all_paths);
				free_all(shell, "no print\n", 0);
				return (NULL) ;
			}
		}
		i++;
	}
	write(2, argv[0], ft_strlen(argv[0]));
	if (ft_strlen(argv[0]) > 0)
		write(2, ": command not found\n", 20);
	free_d_str(all_paths);
	free_all(shell, "no print\n", 0);
	shell->exit_status = 127;
	return (NULL);
}

char	*ft_execve(char *path, char **argv, t_shell *shell)//shell
{
	char		**all_paths;
	pid_t	pid;
	int pipefd[2];

	if (argv[0] == NULL)
		return (NULL);
	if (is_directory(path) == 1)
	{
		printf("bash: %s: Is a directory\n", argv[0]);
		free_all(shell, "no print\n", 126);
		return (NULL);
	}
	if (access(path, X_OK) == 0)
	{
		pipe(pipefd);
		if ((pid = fork()) == -1)
			free_all(shell, "fork failed\n", 127);
		if (pid == 0)	
		{
			close(pipefd[0]);
			sig_int = getpid();
			write(pipefd[1], ft_itoa(sig_int), ft_strlen(ft_itoa(sig_int)));
			// printf("here\n");
			execve(path, argv, shell->env);
			free_all(shell, "execve failed\n", 127);
		}
		else
		{
			close(pipefd[1]);
			char buffer[1024];
			read(pipefd[0], buffer, sizeof(buffer));
			sig_int = ft_atoi(buffer);
			// printf("pid: %d\n", sig_int);
			free_all(shell, "no print\n", 0);
			return (wait(NULL), NULL);
		}
	}
	all_paths = append_path(ft_split(ft_getenv("PATH", shell->env), ':'), ft_strjoin("/", path));
	if (all_paths == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	return (path_run(all_paths, argv, shell->env, shell));
}