/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 17:22:31 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fork_ft(t_token_type *t_type, char **inp, char *in, char **hdoc)
{
	int	fd;

	if (*t_type == D_LESS)
		*inp = temp_hdoc(hdoc[0]);
	if (*t_type == LESS)
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

void	wait_ft(t_token_type t_type, char *inp)
{
	wait(NULL);
	if (t_type == D_LESS)
		unlink(inp);
	exit(0);
}

void	pipe_inp_cmd_run(t_table exp_table, char *in, char **hdoc, \
t_shell *shell)
{
	int				fd;
	int				pid;
	char			*inp;
	t_token_type	t_type;

	inp = NULL;
	t_type = in_o_hdoc(shell->tokens, shell->table_id);
	fd = init_fork_ft(&t_type, &inp, in, hdoc);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
	pid = fork();
	if (pid == -1)
		(free_d_str(hdoc), free_all(shell, "Fork Fail\n", 127));
	if (pid == 0)
		ft_pipe_execve(exp_table.args[0], exp_table.args, shell);
	else
	{
		free_d_str(hdoc);
		free_all(shell, "no print", 127);
		wait_ft(t_type, inp);
	}
}

void	pipe_exec_run(t_table table, int table_id, char **hdoc, t_shell *shell)
{
	char	*in;

	in = check_in(table);
	output_check(table, table_id, shell->tokens);
	shell->table_id = table_id;
	if (is_builtin(table.args[0]) == 1)
	{
		free_d_str(hdoc);
		run_builtin(table, shell);
		free_all_env(shell->env);
		free_all_env(shell->exported);
		exit(shell->exit_status);
	}
	else if (table.args[1] != NULL || (table.in[0] == NULL \
	&& table.heredoc[0] == NULL))
	{
		free_d_str(hdoc);
		ft_pipe_execve(table.args[0], table.args, shell);
	}
	else
		pipe_inp_cmd_run(table, in, hdoc, shell);
}
