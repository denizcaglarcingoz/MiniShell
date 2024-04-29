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
	int		i;
	pid_t	pid;
	i = 0;
	
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0)
		{	
			if ((pid = fork()) == -1)
				return ("fork failed\n");
			if (pid == 0)	
			{
				execve(all_paths[i], argv, environ);
				free_d_str(all_paths);
				// free tables
				perror("execve failed\n");
				return ("execve failed\n");
			}
			else
				wait(NULL);
			break ;
		}
		i++;
	}
	free_d_str(all_paths);
	return (NULL);
}

char	*exter_cmd_run(char *path, char **argv)
{
	char	**environ;
	char		**all_paths;
	pid_t	pid;

	environ = get_full_env(0);
	if (argv[0] == NULL)
		return (NULL);
	if (access(path, X_OK) == 0)
	{
		if ((pid = fork()) == -1)
		{	// fork_fail(exp_table);
		}
		if (pid == 0)	
		{

			execve(path, argv, environ);
			// free tables
			printf("execve failed\n");
			exit(0);
		}
		else
			return (wait(NULL), NULL);
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


