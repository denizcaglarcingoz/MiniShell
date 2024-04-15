#include "minishell.h"

char	**content_dup(char **tabl_str, t_tokens **tokens, t_token_type type)
{
	if (type != STRING)
		*tokens = (*tokens)->next;
	*tabl_str = ft_strdup((*tokens)->content);
	tabl_str++;
	*tokens = (*tokens)->next;
	return (tabl_str);
}

t_tokens	*table_content_init(t_tokens *tokens, t_table table)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tokens = tokens->next;
			return (tokens);
		}
		else if (tokens->type == GREATER)
			table.out = content_dup(table.out, &tokens, GREATER);
		else if (tokens->type == LESS)
			table.in = content_dup(table.in, &tokens, LESS);
		else if (tokens->type == D_GREATER)
			table.append = content_dup(table.append, &tokens, D_GREATER);
		else if (tokens->type == D_LESS)
			table.heredoc = content_dup(table.heredoc, &tokens, D_LESS);
		else if (tokens->type == STRING)
			table.args = content_dup(table.args, &tokens, STRING);
		if (table.args == NULL || table.in == NULL || table.out == NULL
			|| table.append == NULL || table.heredoc == NULL)
		{
			perror("table_init");
			return (NULL);
		}
	}
	return (tokens);
}

t_table	*table_init(t_tokens *tokens, t_table *table)
{
	int			i;

	i = 0;
	while (i < table->table_len)
	{
		if (t_content_alloc(tokens, &table[i]) == -1)
		{
			free_t_content_alloc_and_table(table, i);
			return (NULL);
		}
		tokens = table_content_init(tokens, table[i]);
		if (tokens == NULL && i != table->table_len - 1)
		{
			free_content_first_allocs_only(table[i]);
			free_t_content_alloc_and_table(table, i);
			return (NULL);
		}
		i++;
	}
	return (table);
}
