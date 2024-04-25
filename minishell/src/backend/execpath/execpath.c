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
	int		pipefd[2];
	int		i;
	int		j;
	pid_t	pid;
	i = 0;
	
	j = 0;
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0)
		{	
			j = 1;
			pipe_init_exec(pipefd);
			if ((pid = fork()) == -1)
				return (NULL);
			if (pid == 0)	
			{
				if (execve(all_paths[i], argv, environ) == -1)
				{	
					free_d_str(all_paths);
					return (NULL);
				}
				printf("execve failed\n");
				exit(0);
			}
			else
			{	
				wait(NULL);
				break ;
			}
			
		}
		i++;
	}
 		close(pipefd[0]);
	close(pipefd[1]);
	free_d_str(all_paths);
	return (NULL);
}

char	*exter_cmd_run(char *path, char **argv)
{
	extern char	**environ;
	char		**all_paths;
	int		pipefd[2];
	pid_t	pid;
	char	BUFFER[BUFFER_SIZE];
	int		count_read;
	char	*read_str;

	if (argv[0] == NULL)
		return (NULL);
	if (access(path, X_OK) == 0)
	{
		printf("--------------------------------inside access\n");
		pipe_init_exec(pipefd);
		if ((pid = fork()) == -1)
		{	
			// fork_fail(exp_table);
		}
		if (pid == 0)	
		{
			close(pipefd[0]);
			if (execve(path, argv, environ) == -1)
			{
				perror("execve");
				return (NULL);
			}
			close(pipefd[1]);
			exit(0);
		}else
		{
			close(pipefd[1]);
			while ((count_read = read(pipefd[0], BUFFER, BUFFER_SIZE)) > 0)
			{
				BUFFER[count_read] = '\0';
				read_str = ft_strjoin(read_str, BUFFER);
				// protect this
			}
			wait(NULL);
			return (read_str);
		}
	}
	all_paths = append_path(ft_split(getenv("PATH"), ':'), ft_strjoin("/", path));
	if (all_paths == NULL)
		return (NULL);
	return (path_run(all_paths, argv, environ));
}

// TEST

// int main(int argc, char **argv)
// {
// 	if (argc < 3)
// 	{
// 		printf("Not enough arg\n");
// 		return (1);
// 	}
// 	int x = 0;
// 	while (argv[x] != NULL)
// 	{
// 		write(1, argv[x], ft_strlen(argv[x]));
// 		write(1, "\n", 1);
// 		x++;
// 	}
// 	exter_cmd_run(argv[1], argv);
// 	return (0);
// }


