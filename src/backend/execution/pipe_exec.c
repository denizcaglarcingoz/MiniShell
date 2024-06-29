/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 14:11:28 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern pid_t	g_sig_int;

void	child_pro_helper(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	int	out_check;

	out_check = 0;
	if (prev_read_fd != -1)
		(dup2(prev_read_fd, STDIN_FILENO), close(prev_read_fd));
	if (i + 1 < shell->tables->table_len)
	{
		if (shell->tables[i].args[0] != NULL || shell->tables[i].out[0] != NULL)
		{
			out_check = output_check(shell->tables[i], i, shell->tokens);
			if (out_check == 0)
				dup2(pipefd[1], STDOUT_FILENO);
			else if (out_check == -127)
				(close(pipefd[1]), free_all(shell, "no print", 127));
		}
	}
	if (i + 1 == shell->tables->table_len)
	{
		if (shell->tables[i].args[0] == NULL || shell->tables[i].out[0] != NULL)
		{
			out_check = output_check(shell->tables[i], i, shell->tokens);
			if (out_check == -127)
				(close(pipefd[1]), free_all(shell, "no print", 127));
		}
	}
}

void	child_pro(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	char	**hdoc;

	close(pipefd[0]);
	g_sig_int = 2;
	hdoc = shell->hdoc;
	if (g_sig_int == 1)
	{
		g_sig_int = getpid();
		close(pipefd[1]);
		free_d_str(hdoc);
		free_all(shell, "no exit", 0);
		exit(0);
	}
	g_sig_int = getpid();
	child_pro_helper(shell, pipefd, prev_read_fd, i);
	close(pipefd[1]);
	if ((shell->tables[i]).args[0] == NULL)
		exit(0);
	else
		pipe_exec_run(shell->tables[i], i, hdoc, shell);
}

void	expansion_ok_run(t_shell *shell, t_pipe_exec_var *exec)
{
	exec->pid = pipe_fork(shell, exec->pipefd);
	if (exec->pid == 0)
	{
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
	free_d_str(shell->hdoc);
}

void	pipe_closing_args(t_shell *shell, t_pipe_exec_var *exec)
{
	int		status;
	pid_t	result;

	status = 0;
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_int_exec);
	g_sig_int = exec->pid;
	if (exec->expandor_check == 0)
		(get_exit_code(shell, exec->pid), free_all(shell, "no exit", 3));
	if (exec->expandor_check == 0)
		close(exec->pipefd[0]);
	if (exec->pid != -1)
		result = waitpid(exec->pid, &status, WNOHANG);
	if (exec->pid != -1 && result == 0)
		waitpid(exec->pid, &status, 0);
	dup2(exec->std_in, STDIN_FILENO);
	close(exec->std_in);
	dup2(exec->std_out, STDOUT_FILENO);
	close(exec->std_out);
	signal(SIGQUIT, SIG_IGN);
}

void	pipe_execution(t_shell *shell)
{
	t_pipe_exec_var	exec;

	exec_init(&exec);
	while (exec.i < shell->table_len)
	{
		if (expandor_hdoc(shell, exec.i) == false)
			exec.hdoc_check = 1;
		if (exec.hdoc_check == 0)
			shell->hdoc = check_hdoc(shell->tables[exec.i], shell);
		if (exec.hdoc_check == 0 && expandor(shell, exec.i) == false)
			exec.expandor_check = 1;
		if (exec.expandor_check == 0 && exec.hdoc_check == 0)
			expansion_ok_run(shell, &exec);
		if (exec.i < shell->table_len)
			if (exec.hdoc_check == 0 && exec.expandor_check == 1)
				free_d_str(shell->hdoc);
		(exec.i)++;
		if (exec.i < shell->table_len)
		{
			exec.hdoc_check = 0;
			exec.expandor_check = 0;
		}
	}
	pipe_closing_args(shell, &exec);
}
