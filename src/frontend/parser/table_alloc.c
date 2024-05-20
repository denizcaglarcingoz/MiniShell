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

void t_table_len_assign(t_table *table, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		table[i].table_len = len;
		i++;
	}
}

t_table	*table_alloc(t_tokens *tokens)
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
	{
		perror("table_alloc");
		return (NULL);
	}
	table[len + 1] = struct_null(table[len + 1]);
	t_table_len_assign(table, len + 1);
	return (table);
}
