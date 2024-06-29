/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:07:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 16:11:29 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_check(t_table table, int table_id, t_tokens *tokens)
{
	t_token_type	t_type;
	int				fd;
	char			*out;

	fd = -1;
	if (table.out[0] != NULL || table.append[0] != NULL)
	{
		t_type = out_o_app(table, table_id, tokens);
		if (t_type == ERR_TYPE)
			return (-127);
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
			return (perror("output_check_open"), -127);
		return (dup2(fd, STDOUT_FILENO), close(fd), fd);
	}
	return (0);
}
