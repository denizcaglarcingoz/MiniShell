/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:07:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 01:52:04 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (perror("output_check_dup2"), -127);
		return (close(fd), fd);
	}
	return (-1);
}
