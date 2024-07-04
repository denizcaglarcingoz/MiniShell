/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/03 16:41:22 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	in_o_hdoc(t_tokens *tokens, int table_id)
{
	t_tokens	*first;
	int			i;

	first = start_of_pipe(tokens, table_id);
	if (first == NULL)
		return (NO_TYPE);
	i = 0;
	if (first->type == PIPE)
		first = first->next;
	while (first)
	{
		if (first->type == LESS)
			i = 0;
		else if (first->type == D_LESS)
			i = 1;
		if (first->type == PIPE)
			break ;
		first = first->next;
	}
	if (i == 0)
		return (LESS);
	else
		return (D_LESS);
}

int	create_files(t_table exp_table)
{
	int	i;

	i = 0;
	while (exp_table.out[i] != NULL)
	{
		if (output_file(exp_table.out[i], NULL) == 1)
			return (1);
		i++;
	}
	i = 0;
	while (exp_table.append[i] != NULL)
	{
		if (access(exp_table.append[i], F_OK) == -1)
			if (output_file(exp_table.append[i], NULL) == 1)
				return (1);
		i++;
	}
	return (0);
}

t_token_type	out_o_app(t_table exp_table, int table_id, t_tokens *tokens)
{
	t_tokens	*first;
	int			i;

	if (create_files(exp_table) == 1)
		return (ERR_TYPE);
	first = start_of_pipe(tokens, table_id);
	if (first == NULL)
		return (NO_TYPE);
	if (first->type == PIPE)
		first = first->next;
	i = 2;
	while (first)
	{
		if (first->type == GREATER)
			i = 0;
		else if (first->type == D_GREATER)
			i = 1;
		first = first->next;
		if (first == NULL || first->type == PIPE)
			break ;
	}
	if (i == 0)
		return (GREATER);
	else
		return (D_GREATER);
}
