/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:29:05 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_sig_int;

int	pipe_fork(t_shell *shell, int pipefd[2])
{
	int	pid;

	if (pipe(pipefd) == -1)
		free_all(shell, "Pipe Fail\n", 127);
	pid = fork();
	if (pid == -1)
		free_all(shell, "Fork Fail\n", 127);
	return (pid);
}

void	child_pro_helper(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	if (expandor(shell, i) == false)
		free_all(shell, "no print", 127);
	if (i + 1 < shell->tables->table_len)
	{
		if (shell->tables[i].args[0] != NULL \
		&& output_check(shell->tables[i], i, shell->tokens) == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
	}
	else
		close(pipefd[1]);
}

void	child_pro(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	char	**hdoc;

	close(pipefd[0]);
	g_sig_int = 2;
	hdoc = check_hdoc(shell->tables[i], shell);
	if (g_sig_int == 1)
	{
		g_sig_int = getpid();
		exit(0);
	}
	g_sig_int = getpid();
	child_pro_helper(shell, pipefd, prev_read_fd, i);
	if ((shell->tables[i]).args[0] == NULL)
		exit(0);
	else
		pipe_exec_run(shell->tables[i], i, hdoc, shell);
}

void	ft_wait(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->tables->table_len)
	{
		wait(NULL);
		i++;
	}
	free_all(shell, "no exit", 0);
}

void	pipe_execution(t_shell *shell)
{
	int		pipefd[2];
	int		prev_read_fd;
	int		pid;
	int		i;

	i = 0;
	prev_read_fd = -1;
	while (i < shell->tables->table_len)
	{
		pid = pipe_fork(shell, pipefd);
		if (pid == 0)
			child_pro(shell, pipefd, prev_read_fd, i);
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
	ft_wait (shell);
}
