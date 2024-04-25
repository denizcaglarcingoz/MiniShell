#include "minishell.h"

void free_table(t_table *exp_table)
{
	free(exp_table);
	// proper free
}

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

void	parent_process(int pipefd, int in_fd)
{
	dup(in_fd);
	dup(pipefd);

	wait(NULL);
}

// void	child_process(t_table *exp_table, int *pipefd, int i, int out_fd)
// {
// 	if (i + 1 < exp_table->table_len)
// 	{
// 		pipe_exec_run(exp_table[i], pipefd[1], 0);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		dup2(out_fd, STDOUT_FILENO);
// 		single_exec(exp_table[i], 0);
// 	}
// 	//run_command(exp_table[i], i, pipefd[1], out_fd);
// 	close(pipefd[1]);
// }

void pipe_execution(t_table *exp_table)
{
	int		pipefd[2];
	int		in_fd;
	int		out_fd;
	// pid_t	pid;
	int		i;

	i = 0;
	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	pipe_init(exp_table, pipefd);
	while (i < exp_table->table_len)
	{
		dup2(out_fd, STDOUT_FILENO);
		if (i + 1 < exp_table->table_len)
			pipe_exec_run(exp_table[i], pipefd[1], i);
		else
		{
			single_exec(exp_table[i], i);
			dup2(out_fd, STDOUT_FILENO);
			dup2(in_fd, STDIN_FILENO);
			break ;
		}
		i++;
	}
}
