/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_alloc copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:26:25 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:50:38 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	struct_null(t_table table)
{
	table.args = NULL;
	table.in = NULL;
	table.out = NULL;
	table.append = NULL;
	table.heredoc = NULL;
	return (table);
}

static void	t_table_len_assign(t_table *table, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		table[i].table_len = len;
		i++;
	}
}

t_table	*table_alloc(t_tokens *tokens, t_shell *shell)
{
	int			len;
	t_table		*table;

	len = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			len++;
		tokens = tokens->next;
	}
	table = malloc(sizeof(t_table) * (len + 2));
	if (table == NULL)
		free_all(shell, "table_alloc malloc failure", 2);
	table[len + 1] = struct_null(table[len + 1]);
	t_table_len_assign(table, len + 1);
	return (table);
}
