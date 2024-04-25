#include "minishell.h"

t_token_type in_o_hdoc(t_table exp_table, int table_id)
{
	t_tokens *first;
	int i;

	first = start_of_pipe(exp_table.tokens, table_id);
	if (first == NULL)
		return (NO_TYPE);
	i = 0;
	while(first)
	{
		if(first->type == LESS)
			i = 0;
		else if (first->type == D_LESS)
			i = 1;
		first = first->next;
	}
	if (i == 0)
		return (LESS);
	else
		return (D_LESS);
}

void create_files(t_table exp_table)
{
	int i;

	i = 0;
	while (exp_table.out[i] != NULL)
	{
		output_file(exp_table.out[i], NULL);
		i++;
	}
	i = 0;
	while (exp_table.append[i] != NULL)
	{
		if (access(exp_table.append[i], F_OK) == -1)
			output_file(exp_table.append[i], NULL);
		i++;
	}
}

t_token_type out_o_app(t_table exp_table, int table_id)
{
	t_tokens *first;
	int i;

	create_files(exp_table);
	first = start_of_pipe(exp_table.tokens, table_id);
	if (first == NULL)
		return (NO_TYPE);
	if (first->type== PIPE)
		first = first->next;
	printf("first->type: %s\n", first->content);
	i = 2;
	while(first)
	{
		if(first->type == GREATER)
			i = 0;
		else if (first->type == D_GREATER)
			i = 1;
		first = first->next;
		if (first == NULL || first->type == PIPE)
			break;
	}
	if (i == 0)
		return (GREATER);
	else
		return (D_GREATER);
}
