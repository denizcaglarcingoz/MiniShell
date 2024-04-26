#include "minishell.h"


// void command_init(t_tokens *tokens, t_table *table) -- echo deniz
// voic expand_check(t_tokens *tokens, t_table *table) -- $NO echo deniz

t_table *parser(t_tokens *tokens)
{
	t_tokens	*first_token;
	t_table		*table;
	
	table = NULL;
	first_token = tokens;
	if (tokens == NULL)
		return (NULL);
	table = table_alloc(tokens);
	//if (table == NULL)
		// free and exit;
	table = table_init(tokens, table);
	int i = 0;
	while (table[i].args != NULL)
	{
		table[i].tokens = tokens;
		i++;
	}
	return (table);
}

int print_tables(t_table *table)
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
	return  0;
}