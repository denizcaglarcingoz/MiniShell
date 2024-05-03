/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/04/29 19:57:31 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_inp_cmd_run(t_table exp_table, char *in, char **hdoc, int is_out)
{
	int				fd;
	int				in_fd;
	char			*inp;
	t_token_type	t_type;

	t_type = in_o_hdoc(exp_table, 0);
	if (t_type == D_LESS)
		inp = temp_hdoc(hdoc[0]);
	if (t_type == LESS)
		inp = in;
	fd = open(inp, 0);
	if (fd == -1)
	{	
		perror("open");
		return ;
	}
	in_fd = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	ft_pipe_execve(exp_table.args[0], exp_table.args, is_out);
	dup2(in_fd, STDIN_FILENO);
	if (t_type == D_LESS)
		unlink(inp);
	close(fd);
}

void	pipe_exec_run(t_table table, int table_id, char **hdoc)
{
	char *in;
	int	is_out;

	in = check_in(table);
	is_out = output_check(table, table_id);
	if (is_builtin(table.args[0]) == 1)
	{	
		run_builtin(table);
		// clean up
		exit(0);
	}
	else if (table.args[1] != NULL || (table.in[0] == NULL && table.heredoc[0] == NULL))
		ft_pipe_execve(table.args[0], table.args, is_out);
	else
		pipe_inp_cmd_run(table, in, hdoc, is_out);
}
