#include "minishell.h"
void	print_result(int prev_read_fd)
{
	char	buffer[BUFSIZ];
    ssize_t	count_read;
    
	while ((count_read = read(prev_read_fd, buffer, BUFSIZ)) > 0)
        write(STDOUT_FILENO, buffer, count_read);
}

void	free_matrix_2(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*try_path;
	char	*left_part;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		left_part = ft_strjoin(paths[i], "/");
		if (!left_part)
			break ;
		try_path = ft_strjoin(left_part, cmd);
		if (!try_path)
		{
			free(left_part);
			break ;
		}
		free(left_part);
		if (access(try_path, F_OK) == 0)
			return (try_path);
		free(try_path);
	}
	free_matrix_2(paths);
	return (NULL);
}

char	**return_expanded(char **args, t_shell *shell)//join args to put through expander as char *. then split again.
{
	int		i;

	i = -1;
	while (args[++i])
		args[i] = expander(args[i], shell);
	//ft_putstr_color_fd(1, args[0], BLUE); testing
	return (args);
}

static void	exec_cmd(char **full_cmd, char **envp)
{
	char	*path;
	
	path = get_path(full_cmd[0], envp);
	//ft_putstr_color_fd(2, path, RED);// test
	if (!path)
	{
		perror("Error: Unable to find executable for command");
		//free_stuff or use ft_exit when its ready
		exit(EXIT_FAILURE);
	}
	if (execve(path, full_cmd, envp) == -1)
	{
		perror("execve error");
		//free_stuff
		exit(EXIT_FAILURE);
	}
}

void	executor(t_table *table, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;
	int		i;
	int		p_fd[2];
	extern char	**environ;

	//(void)shell;
	prev_read_fd = STDIN_FILENO;
	i = -1;
	while (++i < table->table_len)
	{
		table[i].args = return_expanded((table[i].args), shell);
		if (check_and_run_builtins(table, table[i].args, shell) == 2)//for some built ins, should finish without continuing, like pwd etc.
			return ;//return for certain builtins
		if (pipe(p_fd) == -1)
			perror("pipe");//handle
		pid = fork();
		if (pid < 0)
			perror("fork");//	error_handle;
		else if (pid == 0)
		{
			close(p_fd[0]);
			if (dup2(prev_read_fd, STDIN_FILENO) == -1)
				perror("dup2");//handle
			if (dup2(p_fd[1], STDOUT_FILENO) == -1)
				perror("dup2");//handle
			close(p_fd[1]);
			exec_cmd(table[i].args, environ);
		}
		else
		{
			close(p_fd[1]);
			if (prev_read_fd != STDIN_FILENO)
				close(prev_read_fd);
			prev_read_fd = p_fd[0];
		}
	}
	print_result(prev_read_fd);
	close(prev_read_fd);
	i = -1;
	while (++i < table->table_len)
		wait(NULL);
}
