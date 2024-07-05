/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 04:58:07 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pipe_fork(t_shell *shell, int pipefd[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		free_all(shell, "Pipe Fail\n", 127);
	pid = fork();
	if (pid == -1)
		free_all(shell, "Fork Fail\n", 127);
	return (pid);
}

void	exec_init(t_pipe_exec_var *exec, t_shell *shell)
{
	exec->pid = -1;
	exec->str_pid = malloc(sizeof(pid_t) * shell->tables->table_len);
	if (exec->str_pid == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	exec->i = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->prev_read_fd = -1;
	exec->expandor_check = 0;
	exec->hdoc_check = 0;
	exec->std_in = dup(STDIN_FILENO);
	if (exec->std_in == -1)
		(free(exec->str_pid), free_all(shell, "dup fail", 127));
	exec->std_out = dup(STDOUT_FILENO);
	if (exec->std_out == -1)
	{
		close(exec->std_in);
		free(exec->str_pid);
		free_all(shell, "dup fail", 127);
	}
}
