/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_out_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 04:54:24 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 04:57:32 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_prev_read_fd(t_shell *shell, int pipefd1, int prev_read_fd)
{
	int	dup_res;

	if (prev_read_fd != -1)
	{
		dup_res = dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
		if (dup_res == -1)
		{
			close(pipefd1);
			free_all(shell, "dup2 error", 127);
		}
	}
}

void	child_no_out_file(t_shell *shell, int pipefd1)
{
	int	dup_res;

	dup_res = dup2(pipefd1, STDOUT_FILENO);
	close(pipefd1);
	if (dup_res == -1)
		free_all(shell, "dup2 error", 127);
}

void	child_out_check(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	int	out_check;

	out_check = -1;
	first_prev_read_fd(shell, pipefd[1], prev_read_fd);
	if (i + 1 < shell->tables->table_len)
	{
		if (shell->tables[i].args[0] != NULL || shell->tables[i].out[0] != NULL)
		{
			out_check = output_check(shell->tables[i], i, shell->tokens);
			if (out_check == -1)
				child_no_out_file(shell, pipefd[1]);
		}
	}
	if (i + 1 == shell->tables->table_len)
		if (shell->tables[i].args[0] == NULL || shell->tables[i].out[0] != NULL)
			out_check = output_check(shell->tables[i], i, shell->tokens);
	if (out_check == -127)
		(close(pipefd[1]), free_all(shell, "no print", 127));
}
