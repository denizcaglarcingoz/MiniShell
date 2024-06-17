/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_content_alloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:05 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:27:06 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_table_content_len	int_zero_init(void)
{
	t_table_content_len	table_content_len;

	table_content_len.args = 0;
	table_content_len.in = 0;
	table_content_len.out = 0;
	table_content_len.append = 0;
	table_content_len.heredoc = 0;
	table_content_len.err = 0;
	return (table_content_len);
}

static	t_table_content_len	content_lens(t_tokens *tokens, \
t_table_content_len t_c_len)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (t_c_len);
		if (tokens->type == STRING && ft_strlen(tokens->content) > 0)
			t_c_len.args++;
		else if (tokens->type == GREATER)
			t_c_len.out++;
		else if (tokens->type == LESS)
			t_c_len.in++;
		else if (tokens->type == D_GREATER)
			t_c_len.append++;
		else if (tokens->type == D_LESS)
			t_c_len.heredoc++;
		if (tokens->type == LESS || tokens->type == GREATER \
		|| tokens->type == D_LESS || tokens->type == D_GREATER)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (t_c_len);
}

static void	set_to_null(t_table *table, t_table_content_len table_content_len)
{
	table->args[table_content_len.args] = NULL;
	table->in[table_content_len.in] = NULL;
	table->out[table_content_len.out] = NULL;
	table->append[table_content_len.append] = NULL;
	table->heredoc[table_content_len.heredoc] = NULL;
}

int	t_content_alloc(t_tokens *tokens, t_table *table)
{
	t_table_content_len	table_content_len;

	table_content_len = int_zero_init();
	table_content_len = content_lens(tokens, table_content_len);
	table->args = malloc(sizeof(char *) * (table_content_len.args + 1));
	table->in = malloc(sizeof(char *) * (table_content_len.in + 1));
	table->out = malloc(sizeof(char *) * (table_content_len.out + 1));
	table->append = malloc(sizeof(char *) * (table_content_len.append + 1));
	table->heredoc = malloc(sizeof(char *) * (table_content_len.heredoc + 1));
	if (table->args == NULL || table->in == NULL || table->out == NULL \
	|| table->append == NULL || table->heredoc == NULL)
	{
		free_content_first_allocs_only(table);
		return (-1);
	}
	set_to_null(table, table_content_len);
	return (0);
}
