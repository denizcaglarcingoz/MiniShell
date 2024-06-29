/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 20:00:08 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern pid_t	g_sig_int;

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
	exec->prev_read_fd = -1;
	exec->expandor_check = 0;
	exec->hdoc_check = 0;
	exec->std_in = dup(STDIN_FILENO);
	exec->std_out = dup(STDOUT_FILENO);
}
