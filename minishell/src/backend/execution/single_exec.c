/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/04/25 18:45:37 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *temp_hdoc(char *hdoc)
{
	int fd;

	fd = open("temp_hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), NULL);
	write(fd, hdoc, ft_strlen(hdoc));
	close(fd);
	return ("temp_hdoc");
}

void	inp_cmd_run(t_table exp_table, char *in, char **hdoc)
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
	return_out = exter_cmd_run(exp_table.args[0], exp_table.args);
	dup2(in_fd, STDIN_FILENO);
	if (t_type == D_LESS)
		unlink(inp);
	close(fd);
}

int	output_check(t_table exp_table, int table_id)
{
	t_token_type t_type;
	int fd;
	char *out;

	if (exp_table.out[0] != NULL || exp_table.append[0] != NULL)
	{
		printf("table_id: %d\n", table_id);	
		t_type = out_o_app(exp_table, table_id);
		if (t_type == GREATER)
		{	
			printf("in output\n");
			out = last_str(exp_table.out);
		
		}
		if (t_type == D_GREATER)
		{
			printf("in append\n");
			out = last_str(exp_table.append);
		}
		printf("out: %s\n", out);
		fd = open(out, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{	
			printf("minishell: %s: %s\n", out, strerror(errno));
			return (perror("open"), 0);}
		dup2(fd, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	single_exec(t_table exp_table, int table_id)
{
	char **hdoc;
	char *in;
	int out_fd;
	int	is_out;

	// if (is_builtin(exp_table.args[0]) == 1) // run_builtin is a function that is inside of builtins
	// 	return(run_builtin());
	out_fd = dup(STDOUT_FILENO);
	hdoc = check_hdoc(exp_table);
	in = check_in(exp_table);
	is_out = output_check(exp_table, table_id);
	if (exp_table.args[1] == NULL && exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL &&
			exp_table.my_stdin[0] != NULL)
		exter_cmd_run(exp_table.args[0], exp_table.args);
	else if (exp_table.args[1] != NULL || (exp_table.in[0] == NULL && exp_table.heredoc[0] == NULL))
		exter_cmd_run(exp_table.args[0], exp_table.args);
	else
		inp_cmd_run(exp_table, in, hdoc);
	if (is_out == 1)
		dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}
