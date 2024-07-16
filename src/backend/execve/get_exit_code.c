/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:43 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/16 18:35:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_code(t_shell *shell, pid_t pid)
{
	int		child_exit_code;
	int		status;
	pid_t	wait_result;
	int		i;

	i = 0;
	while (i < shell->table_len)
	{
		wait_result = waitpid(pid, &status, 0);
		if (wait_result == pid)
		{
			if (WIFEXITED(status))
			{
				child_exit_code = WEXITSTATUS(status);
				shell->exit_status = child_exit_code;
			}
			else
				shell->exit_status = 127;
		}
		i++;
	}
}

void	get_exit_code_p(t_shell *shell, t_pipe_exec_var *exec)
{
	int		child_exit_code;
	int		status;
	pid_t	wait_result;
	int		i;

	i = 0;
	if (g_sig_int != SIGUSR1)
	{
		while (i < shell->table_len)
		{
			wait_result = waitpid(exec->str_pid[i], &status, 0);
			if (wait_result == exec->pid)
			{
				if (WIFEXITED(status))
				{
					child_exit_code = WEXITSTATUS(status);
					shell->exit_status = child_exit_code;
				}
				else
					shell->exit_status = 127;
			}
			i++;
		}
	}
}

void	path_run_signals(pid_t pid, t_shell *shell)
{
	shell->pid = ft_pid(shell);
	signal(SIGINT, sigint_handler_int_exec);
	signal(SIGQUIT, sigint_handler_quit);
	get_exit_code(shell, pid);
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
}
