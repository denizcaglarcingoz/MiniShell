/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/05/09 23:36:15 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *temp_hdoc(char *hdoc)
{
	int fd;

	fd = open("temp_hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open: temp_hdoc"), NULL);
	write(fd, hdoc, ft_strlen(hdoc));
	close(fd);
	return ("temp_hdoc");
}

void	inp_cmd_run(t_table exp_table, char *in, char **hdoc, t_shell *shell)
{
	int				fd;
	int				in_fd;
	char			*inp;
	t_token_type	t_type;

	t_type = in_o_hdoc(shell->tokens, 0);
	if (t_type == D_LESS)
		inp = temp_hdoc(hdoc[0]);
	if (t_type == LESS)
		inp = in;
	fd = open(inp, 0);
	if (fd == -1)
	{	
		perror("open: in_cmd_run");
		return ;
	}
	in_fd = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_execve(exp_table.args[0], exp_table.args, shell); 
	dup2(in_fd, STDIN_FILENO);
	if (t_type == D_LESS)
		unlink(inp);
}

int	output_check(t_table table, int table_id, t_tokens  *tokens)
{
	t_token_type t_type;
	int fd;
	char *out;

	fd = -1;
	if (table.out[0] != NULL || table.append[0] != NULL)
	{
		t_type = out_o_app(table, table_id, tokens);
		if (t_type == GREATER)
		{	
			out = last_str(table.out);
			fd = open(out, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		if (t_type == D_GREATER)
		{
			out = last_str(table.append);
		fd = open(out, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		if (fd == -1)
			return (perror("output_check_open"), 0);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (fd);
	}
	return (0);
}

void	single_exec(t_shell *shell)// shell
{
	char **hdoc;
	char *in;
	int out_fd;
	int	is_out;

	out_fd = dup(STDOUT_FILENO);
	if (expandor(shell, 0) == false)
		return ;
	hdoc = check_hdoc(shell->tables[0]);
	in = check_in(shell->tables[0]);
	is_out = output_check(shell->tables[0], 0, shell->tokens);
	if (is_builtin(shell->tables[0].args[0]) == 1)
		run_builtin(shell->tables[0], shell);
	else if (shell->tables[0].args[1] != NULL || (shell->tables[0].in[0] == NULL && shell->tables[0].heredoc[0] == NULL))
		ft_execve(shell->tables[0].args[0], shell->tables[0].args, shell);
	else
		inp_cmd_run(shell->tables[0], in, hdoc, shell);
	if (is_out != 0)
		dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

// in the situation where expanded element is not good to run table is going to return args[0] as NULL
// It is not faill