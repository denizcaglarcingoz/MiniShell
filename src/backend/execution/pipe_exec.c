/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/16 19:37:36 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_pro(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	char	*in;

	close(pipefd[0]);
	in = check_in(shell->tables[i]);
	if (shell->tables[i].in[0] != NULL && in == NULL)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		if (prev_read_fd != -1)
			close(prev_read_fd);
		close(pipefd[1]);
		not_in_file_p(shell->tables[i].in, shell, i);
	}
	child_out_check(shell, pipefd, prev_read_fd, i);
	close(pipefd[1]);
	if ((shell->tables[i]).args[0] == NULL)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		free_all(shell, "", -1);
	}
	else
		pipe_exec_run(shell->tables[i], i, shell, in);
}

void	expansion_ok_run(t_shell *shell, t_pipe_exec_var *exec)
{
	exec->pid = pipe_fork(shell, exec->pipefd);
	if (exec->pid == 0)
	{
		free(exec->str_pid);
		close(exec->std_in);
		close(exec->std_out);
		child_pro(shell, exec->pipefd, exec->prev_read_fd, exec->i);
	}
	else
	{
		close(exec->pipefd[1]);
		if (exec->prev_read_fd != -1)
			close(exec->prev_read_fd);
		exec->prev_read_fd = exec->pipefd[0];
	}
}

void	pipe_execution(t_shell *shell, t_pipe_exec_var *exec)
{
	exec_init(exec, shell);
	if (pipe_hdocs(shell) == 1)
	{
		signal(SIGINT, sigint_handler_sigint);
		kill(0, SIGINT);
		signal(SIGINT, sigint_handler_int);
		return ;
	}
	while (exec->i < shell->table_len)
	{
		if (expandor(shell, exec->i) == false)
			exec->expandor_check = 1;
		if (exec->expandor_check == 0)
			expansion_ok_run(shell, exec);
		exec->str_pid[exec->i] = exec->pid;
		(exec->i)++;
		if (exec->i < shell->table_len)
			exec->expandor_check = 0;
	}
	pipe_closing_args(shell, exec);
}
