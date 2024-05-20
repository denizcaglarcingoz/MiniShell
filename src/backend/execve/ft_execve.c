#include "minishell.h"

extern pid_t g_sig_int;

void	pipe_init_exec(int pipefd[2], t_shell *shell)//not being used..?
{
	if (pipe(pipefd) == -1)
	{
		free_all(shell, "Pipe creation failed", 127);
		exit(EXIT_FAILURE);
	}
}

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
		free(path_add);
		free_d_str(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		if (!new[i])
		{
			free_matrix(new, i);
			free(path_add);
			free_d_str(str);
			return (NULL);
		}
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
			pid = fork();
			if (pid == -1)
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
				return (NULL);
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

char	*ft_execve(char *path, char **argv, t_shell *shell)
{
	char	**all_paths;
	pid_t	pid;
	int		pipefd[2];
	char	buffer[1024];

	if (argv[0] == NULL)
		return (NULL);
	if (is_directory(path) == 1)
	{
		printf("minishell: %s: Is a directory\n", argv[0]);
		free_all(shell, "no print\n", 126);
		return (NULL);
	}
	if (access(path, X_OK) == 0)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
			free_all(shell, "fork failed\n", 127);
		if (pid == 0)	
		{
			close(pipefd[0]);
			g_sig_int = getpid();
			write(pipefd[1], ft_itoa(g_sig_int), ft_strlen(ft_itoa(g_sig_int)));//must protect itoa
			// printf("here\n");
			execve(path, argv, shell->env);
			free_all(shell, "execve failed\n", 127);
		}
		else
		{
			close(pipefd[1]);
			read(pipefd[0], buffer, sizeof(buffer));
			g_sig_int = ft_atoi(buffer);
			// printf("pid: %d\n", g_sig_int);
			free_all(shell, "no print\n", 0);
			return (wait(NULL), NULL);
		}
	}
	all_paths = append_path(ft_split(ft_getenv("PATH", shell->env), ':'), ft_strjoin("/", path));//must protect for cases split fail, or split success and join fail.
	if (all_paths == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	return (path_run(all_paths, argv, shell->env, shell));
}
