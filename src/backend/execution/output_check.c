/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:07:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 08:53:22 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_is_directory(char *redir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

int	fd_open_out(char **outs)
{
	int		fd;
	char	*out;

	out = last_str(outs);
	fd = open(out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("output_check_open"), -127);
	return (fd);
}

int	fd_open_append(char **append)
{
	int		fd;
	char	*out;

	out = last_str(append);
	if (is_directory(out) == 1)
		return (print_is_directory(out), -127);
	fd = open(out, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("output_check_open"), -127);
	return (fd);
}

int	output_check(t_table table, int table_id, t_tokens *tokens)
{
	t_token_type	t_type;
	int				fd;
	int				dup_res;

	fd = -1;
	if (table.out[0] != NULL || table.append[0] != NULL)
	{
		t_type = out_o_app(table, table_id, tokens);
		if (t_type == ERR_TYPE)
			return (-127);
		if (t_type == GREATER)
			fd = fd_open_out(table.out);
		if (t_type == D_GREATER)
			fd = fd_open_append(table.append);
		dup_res = dup2(fd, STDOUT_FILENO);
		if (dup_res == -1 || fd == -1)
			return (-127);
		return (close(fd), fd);
	}
	return (-1);
}
