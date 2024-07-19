/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 03:47:21 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_inp_fd(t_token_type *t_type, char **inp, char *in, t_shell *shell)
{
	int	fd;

	if (*t_type == D_LESS)
		return (fd_write_hdoc(shell->hdoc[shell->exec.i]));
	*inp = in;
	if (*inp == NULL)
		return (-1);
	fd = open(*inp, 0);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

void	pipe_inp_cmd_run(t_table exp_table, char *in, t_shell *shell)
{
	int				dup_res;
	int				fd;
	char			*inp;
	t_token_type	t_type;

	inp = NULL;
	t_type = in_o_hdoc(shell->tokens, shell->table_id);
	fd = init_inp_fd(&t_type, &inp, in, shell);
	if (fd == -1)
		return ;
	free_d_str_till(shell->hdoc, shell->table_len - 1);
	dup_res = dup2(fd, STDIN_FILENO);
	if (dup_res == -1)
	{
		close(fd);
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		free_all(shell, "dup2 error", 127);
	}
	close(fd);
	ft_pipe_execve(exp_table.args[0], exp_table.args, shell);
}

void	pipe_exec_run(t_table table, int table_id, t_shell *shell, char *in)
{
	shell->table_id = table_id;
	if (is_builtin(table.args[0]) == 1)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		run_builtin(table, shell);
		free_all_env(shell->env);
		free_all_env(shell->exported);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(shell->exit_status);
	}
	else if ((table.args[1] != NULL || table.heredoc[0] == NULL) \
	&& table.in[0] == NULL)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		ft_pipe_execve(table.args[0], table.args, shell);
	}
	else
		pipe_inp_cmd_run(table, in, shell);
}
