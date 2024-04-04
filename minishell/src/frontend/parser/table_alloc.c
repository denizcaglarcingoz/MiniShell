#include "minishell.h"

t_table struct_null(t_table table)
{
	table.in = NULL;
	table.out = NULL;
	table.err = NULL;
	table.pipe = NULL;
	return (table);
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
	table->table_len = len + 1;
	table[len + 1] = struct_null(table[len + 1]);
	return (table);
}
