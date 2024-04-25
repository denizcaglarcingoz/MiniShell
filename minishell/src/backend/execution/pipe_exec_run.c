/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/04/25 17:32:19 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_inp_cmd_run(t_table exp_table, char *in, char **hdoc, int is_out)
{
	int				fd;
	int				in_fd;
	char			*inp;
	char			*return_out;
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
	return_out = pipe_exter_cmd_run(exp_table.args[0], exp_table.args, is_out);
	dup2(in_fd, STDIN_FILENO);
	if (t_type == D_LESS)
		unlink(inp);
	close(fd);
}
void	pipe_exec_run(t_table exp_table, int pipefd1, int table_id)
{
	char **hdoc;
	char *in;
	int out_fd;
	int	is_out;

	// if (is_builtin(exp_table.args[0]) == 1) // run_builtin is a function that is inside of builtins
	// 	return(run_builtin());
	dup(pipefd1);
	out_fd = dup(STDOUT_FILENO);
	hdoc = check_hdoc(exp_table);
	in = check_in(exp_table);
	is_out = output_check(exp_table, table_id);
	if (exp_table.args[1] == NULL && exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL &&
			exp_table.my_stdin[0] != NULL)
		pipe_exter_cmd_run(exp_table.args[0], exp_table.args, is_out);
	else if (exp_table.args[1] != NULL || (exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL))
		pipe_exter_cmd_run(exp_table.args[0], exp_table.args, is_out);
	else
		pipe_inp_cmd_run(exp_table, in, hdoc, is_out);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}
