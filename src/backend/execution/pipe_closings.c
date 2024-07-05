/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_closings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:09:05 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 02:37:17 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_closing_sigs(t_shell *shell, t_pipe_exec_var *exec)
{
	int	dup_res;

	dup_res = dup2(exec->std_in, STDIN_FILENO);
	if (dup_res == -1)
		free_all(shell, "dup2 fail", 127);
	close(exec->std_in);
	dup_res = dup2(exec->std_out, STDOUT_FILENO);
	if (dup_res == -1)
		free_all(shell, "dup2 fail", 127);
	close(exec->std_out);
	free(exec->str_pid);
	signal(SIGINT, sigint_handler_sigint);
	kill(0, SIGINT);
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
}

void	pipe_closing_args(t_shell *shell, t_pipe_exec_var *exec)
{
	int		status;
	pid_t	result;

	status = 0;
	if (g_sig_int == SIGUSR1)
		free_d_str(shell->hdoc);
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_int_exec);
	if (exec->expandor_check == 0)
	{
		get_exit_code_p(shell, exec);
		free_all(shell, "no exit", 3);
	}
	if (exec->expandor_check == 0 && exec->pipefd[0] != -1)
		close(exec->pipefd[0]);
	if (exec->pid != -1)
		result = waitpid(exec->pid, &status, WNOHANG);
	if (exec->pid != -1 && result == 0)
		waitpid(exec->pid, &status, 0);
	free_d_str_till(shell->hdoc, shell->table_len - 1);
	status = dup2(exec->std_in, STDIN_FILENO);
	if (status == -1)
		exit(127);
	pipe_closing_sigs(shell, exec);
}
