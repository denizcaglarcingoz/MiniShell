/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:08 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 02:14:46 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**content_dup(char **tabl_str, t_tokens **tokens, t_token_type type)
{
	if (type != STRING)
		*tokens = (*tokens)->next;
	*tabl_str = ft_strdup((*tokens)->content);
	if (*tabl_str == NULL)
		return (NULL);
	tabl_str++;
	*tokens = (*tokens)->next;
	return (tabl_str);
}

void	clear_exit(t_table *table, t_shell *shell, int i)
{
	free_t_content_alloc_and_table(table, i);
	free_all(shell, "table_alloc failure", 2);
}

t_tokens	*content_init_tokens(t_tokens *tokens, t_table *table, \
t_shell *shell, int i)
{
	if (tokens->type == GREATER)
		table->out = content_dup(table->out, &tokens, GREATER);
	else if (tokens->type == LESS)
		table->in = content_dup(table->in, &tokens, LESS);
	else if (tokens->type == D_GREATER)
		table->append = content_dup(table->append, &tokens, D_GREATER);
	else if (tokens->type == D_LESS)
		table->heredoc = content_dup(table->heredoc, &tokens, D_LESS);
	else if (tokens->type == STRING && ft_strlen(tokens->content) > 0)
		table->args = content_dup(table->args, &tokens, STRING);
	else if (tokens->type == STRING && ft_strlen(tokens->content) == 0)
		tokens = tokens->next;
	if (table->args == NULL || table->in == NULL || table->out == NULL \
	|| table->append == NULL || table->heredoc == NULL)
		clear_exit(table, shell, i);
	return (tokens);
}

t_tokens	*table_content_init(t_tokens *tokens, t_table *tables, \
t_shell *shell, int i)
{
	t_table	table;

	table = tables[i];
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tokens = tokens->next;
			return (tokens);
		}
		tokens = content_init_tokens(tokens, &table, shell, i);
	}
	return (tokens);
}

t_table	*table_init(t_tokens *tokens, t_table *table, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < table->table_len)
	{
		if (t_content_alloc(tokens, &table[i]) == -1)
		{
			free_t_content_alloc_and_table(table, i);
			free_all(shell, "t_content_alloc malloc failure", 4);
			return (NULL);
		}
		tokens = table_content_init(tokens, table, shell, i);
		i++;
	}
	return (table);
}
