#include "minishell.h"

void	pipe_init(t_table *exp_table, int pipefd[2])
{
	if (pipe(pipefd) == -1)
		{
    		perror("Pipe creation failed");
			free_table(exp_table);
    		exit(EXIT_FAILURE);
		}
}

void	fork_fail(t_table *exp_table)
{
	perror("Fork failed");
	free_table(exp_table);
	exit(EXIT_FAILURE);
}

int	pipe_execution(t_table *tables)
{
	int		pipefd[2];
	int		prev_read_fd;
	int		pid;
	int		i;

	i = 0;
	prev_read_fd = -1;
	while (i < tables->table_len)
	{
		pipe_init(tables, pipefd);
		if ((pid = fork()) == -1)
				fork_fail(tables);
		if (pid == 0)	
		{
			close(pipefd[0]);
			if (prev_read_fd != -1)
			{
				dup2(prev_read_fd, STDIN_FILENO);
				close(prev_read_fd);
			}
			char **hdoc = check_hdoc(tables[i]);
			tables[i] = expandor(tables[i]);
			if (i + 1 < tables->table_len)
			{	
				if (tables[i].args[0] != NULL && output_check(tables[i], i) == 0)
					{
						dup2(pipefd[1], STDOUT_FILENO);
						close(pipefd[1]);
					}
			}
			else
				close(pipefd[1]);
			if ((tables[i]).args[0] == NULL)
				return (free_all(tables), 1);
			else
				pipe_exec_run(tables[i], i, hdoc);
			write(2, tables[i].args[0], ft_strlen(tables[i].args[0]));
			write (2, ": command not found\n", 21);
			free_env();
			return (free_all(tables), 1);
		}
		else
		{
			close(pipefd[1]);
			if (prev_read_fd != -1)
				close(prev_read_fd);
			prev_read_fd = pipefd[0];
		}
		i++;
	}
	close(pipefd[0]);
	i = 0;
	while ( i < tables->table_len)
	{
		wait(NULL);
		i++;
	}
	return (free_all(tables), 0);
}
