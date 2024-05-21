#include "minishell.h"

t_table	*parser(t_tokens *tokens, t_shell *shell)
{
	t_table		*table;

	table = NULL;
	if (tokens == NULL)
		return (NULL);
	table = table_alloc(tokens, shell);
	table = table_init(tokens, table, shell);
	return (table);
}

size_t	ft_strlen_double(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* int print_tables(t_table *table)
{
	int i;
	int j;

	i = 0;
	if (table == NULL)
		return (0);
	while (i < table->table_len)
	{
		//printf("table[%d].cmd = %s\n", i, table[i].cmd);
		j = 0;
		while (table[i].args[j] != NULL)
		{
			printf("table[%d].args[%d] = %s\n", i, j, table[i].args[j]);
			// printf("table[%d].args_len = %zu\n", i, \
			ft_strlen_double(table[i].args));
			j++;
		}
		j = 0;
		while (table[i].in[j] != NULL)
		{
			printf("table[%d].in[%d] = %s\n", i, j, table[i].in[j]);
			j++;
		}
		j = 0;
		while (table[i].out[j] != NULL)
		{
			printf("table[%d].out[%d] = %s\n", i, j, table[i].out[j]);
			// printf("table[%d].out_len = %zu\n", i, \
			//ft_strlen_double(table[i].out));
			j++;
		}
		j = 0;
		while (table[i].append[j] != NULL)
		{
			printf("table[%d].append[%d] = %s\n", i, j, table[i].append[j]);
			j++;
		}
		j = 0;
		while (table[i].heredoc[j] != NULL)
		{
			printf("table[%d].heredoc[%d] = %s\n", i, j, table[i].heredoc[j]);
			j++;
		}
		i++;
	}
	return  (0);
} */