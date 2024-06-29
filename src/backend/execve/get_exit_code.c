/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:43 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 19:59:54 by dcingoz          ###   ########.fr       */
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
