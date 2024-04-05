#include "minishell.h"

t_table_content_len	int_zero_init()
{
	t_table_content_len table_content_len;

	table_content_len.args = 0;
	table_content_len.in = 0;
	table_content_len.out = 0;
	table_content_len.append = 0;
	table_content_len.heredoc = 0;
	table_content_len.err = 0;
	return (table_content_len);

}

t_tokens *go_to_job_num(t_tokens *tokens, int table_num)
{
	int pipe_quantity;

	pipe_quantity = 0;
	while (tokens != NULL)
	{
		if(pipe_quantity == table_num)
			return (tokens);
		if (tokens->type == PIPE)
			pipe_quantity++;
		tokens = tokens->next;
	}
	return (tokens);
}

t_table_content_len content_lens(t_tokens *tokens, t_table_content_len t_c_len)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
				return (t_c_len);
		if (tokens->type == STRING)
			t_c_len.args++;
		else if(tokens->type == GREATER)
			t_c_len.out++;
		else if (tokens->type == LESS)
			t_c_len.in++;
		else if (tokens->type == D_GREATER)
			t_c_len.append++;
		else if (tokens->type == D_LESS)
			t_c_len.heredoc++;
		if (tokens->type == LESS || tokens->type == GREATER ||
				tokens->type == D_LESS || tokens->type == D_GREATER)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (t_c_len);
}

void set_to_null(t_table *table, t_table_content_len table_content_len)
{
	table->args[table_content_len.args] = NULL;
	table->in[table_content_len.in] = NULL;
	table->out[table_content_len.out] = NULL;
	table->append[table_content_len.append] = NULL;
	table->heredoc[table_content_len.heredoc] = NULL;
}

void t_content_alloc(t_tokens *tokens, t_table *table)
{
	t_table_content_len table_content_len;

	table_content_len = int_zero_init();
	table_content_len = content_lens(tokens, table_content_len);
	table->args = malloc(sizeof(char *) * (table_content_len.args + 1));
	table->in = malloc(sizeof(char *) * (table_content_len.in + 1));
	table->out = malloc(sizeof(char *) * (table_content_len.out + 1));
	table->append = malloc(sizeof(char *) * (table_content_len.append + 1));
	table->heredoc = malloc(sizeof(char *) * (table_content_len.heredoc + 1));
	if (table->args == NULL || table->in == NULL || table->out == NULL ||
			table->append == NULL || table->heredoc == NULL)
	{
		perror("t_content_init");
		//free tokens and table with function and exit
	}
	set_to_null(table, table_content_len);
}

t_tokens *table_content_init(t_tokens *tokens, t_table table)
{
	while (tokens)
	{
		if(tokens->type == PIPE)
		{
			tokens = tokens->next;
			return (tokens);
		}
		else if (tokens->type == GREATER)
		{
			tokens = tokens->next;
			*table.out = ft_strdup(tokens->content);
			if (*table.out == NULL)
			{
				perror("table_init");
				//free tokens and table with function and exit
			}
			table.out++;
			tokens = tokens->next;
		}
		else if (tokens->type == LESS)
		{
			tokens = tokens->next;
			*table.in = ft_strdup(tokens->content);
			if (*table.in == NULL)
			{
				perror("table_init");
				//free tokens and table with function and exit
			}
			table.in++;
			tokens = tokens->next;
		}
		else if (tokens->type == D_GREATER)
		{
			tokens = tokens->next;
			*table.append = ft_strdup(tokens->content);
			if (*table.append == NULL)
			{
				perror("table_init");
				//free tokens and table with function and exit
			}
			table.append++;
			tokens = tokens->next;
		}
		else if (tokens->type == D_LESS)
		{
			tokens = tokens->next;
			*table.heredoc = ft_strdup(tokens->content);
			if (*table.heredoc == NULL)
			{
				perror("table_init");
				//free tokens and table with function and exit
			}
			table.heredoc++;
			tokens = tokens->next;
		}
		else if (tokens->type == STRING)
		{
			*(table.args) = ft_strdup(tokens->content);
			if (*table.args == NULL)
			{
				perror("table_init");
				//free tokens and table with function and exit
			}
			table.args++;
			tokens = tokens->next;
		}
	}
	return (tokens);
}

t_table *table_init(t_tokens *tokens, t_table *table)
{
	int	i;

	i = 0;
	while(i < table->table_len)
	{
		t_content_alloc(tokens, &table[i]);
		tokens = table_content_init(tokens, table[i]);
		i++;
	}

	return (table);
}
