/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 05:03:34 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 16:14:33 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inp_cmd_run_dups(t_shell *shell, int fd)
{
	int	dup_res;

	shell->in_fd = dup(STDIN_FILENO);
	if (shell->in_fd == -1)
		free_all(shell, "dup", 127);
	dup_res = dup2(fd, STDIN_FILENO);
	close(fd);
	if (dup_res == -1)
		(close(shell->in_fd), free_all(shell, "dup2", 127));
}

void	inp_cmd_run(t_table exp_table, char *in, char **hdoc, t_shell *shell)
{
	int				fd;
	t_token_type	t_type;
	int				dup_res;

	t_type = in_o_hdoc(shell->tokens, 0);
	if (t_type == D_LESS)
		fd = fd_write_hdoc(hdoc[0]);
	free_d_str(hdoc);
	if (t_type == LESS)
		fd = open(in, 0);
	if (fd == -1)
		return (free_all(shell, "open", 127));
	inp_cmd_run_dups(shell, fd);
	ft_execve(exp_table.args[0], exp_table.args, shell);
	dup_res = dup2(shell->in_fd, STDIN_FILENO);
	if (dup_res == -1)
		(close(shell->in_fd), free_all(shell, "dup2", 127));
	close(shell->in_fd);
}

void	single_exec_run(t_shell *shell, t_single_exec_var *var)
{
	shell->out_fd = shell->out_fd;
	if (var->is_out == -1)
		close(shell->out_fd);
	if (shell->tables[0].args[0] == NULL )
		return (free_d_str(var->hdoc), free_all(shell, "no print", 3));
	if (is_builtin(shell->tables[0].args[0]) == 1)
	{
		free_d_str(var->hdoc);
		run_builtin(shell->tables[0], shell);
	}
	else if ((shell->tables[0].args[1] != NULL \
	|| shell->tables[0].heredoc[0] == NULL) && shell->tables[0].in[0] == NULL)
	{
		free_d_str(var->hdoc);
		ft_execve(shell->tables[0].args[0], shell->tables[0].args, shell);
	}
	else
		inp_cmd_run(shell->tables[0], var->in, var->hdoc, shell);
}
