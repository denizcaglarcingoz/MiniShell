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
	if (!path)
	{
		
		ft_putstr_color_fd(2, full_cmd[0], RED);
		ft_putstr_color_fd(2, ": command not found\n", RED);
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


//handle single dollar also..
char	**parse_dollar(t_table *table, char **full_cmd, t_shell *shell)
{
	//ft_putstr_color_fd(2, "nofault\n",  BLUE);
	char	*path;
	DIR		*dir;
	(void)table;
	//if (!(*(*full_cmd + 1)))
	//	return (full_cmd);
	//else
	{
		dir = NULL;
		//path = ft_getenv(full_cmd[0], shell->env);
		while (!(path = ft_getenv(full_cmd[0] + 1, shell->env)) && *(full_cmd + 1))
			full_cmd++; 
		if (path)
			dir = opendir(path);
		if (dir)
		{
			printf(MAGENTA"minishell: %s Is a directory\n"RESET, path);
			closedir(dir);
			shell->exit_status = 126;
			//ft_exit(table, full_cmd, shell);
		}
	}
	return (full_cmd);
}

void	executor(t_table *table, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;
	int		i;
	int		p_fd[2];
	//char	 **full_cmd_start; trying to make way to free when exiting.

	prev_read_fd = STDIN_FILENO;
	i = -1;
	while (++i < table->table_len)
	{
	//ft_putstr_color_fd(2, "nofault\n",  BLUE);

		if ((table[i].args[0][0]) == '$') //maybe make use of strdup then free?
			table[i].args = parse_dollar(table, table[i].args, shell);
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
			if (!check_and_run_builtins_2(table, table[i].args, shell))
				exec_cmd(table[i].args, shell->env);
		exit(EXIT_SUCCESS);
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
