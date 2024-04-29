#include "minishell.h"
char **check_hdoc(t_table exp_table)
{
	int i;
	char *hdoc;
	char **hdocs;

	if (exp_table.heredoc[0] == NULL)
		return (NULL);
	i = 0;
	hdoc = NULL;
	while (exp_table.heredoc[i] != NULL)
	{
		if (hdoc != NULL)
			free(hdoc);
		hdoc = hdoc_inp((exp_table.heredoc)[i]); // hdoc_inp is a function that is inside of redirections heredoc
		i++;
	}
	hdocs = (char **)malloc(sizeof(char *) * 2);
	hdocs[0] = hdoc;
	hdocs[1] = NULL;
	return (hdocs);
}

char *check_in(t_table exp_table)
{
	int i;
	
	if (exp_table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (exp_table.in[i] != NULL)
	{
		if (access(exp_table.in[i], F_OK) == -1)
			return (NULL);
		i++;
	}
	return (exp_table.in[i - 1]);
}

void execution(t_table *exp_table)
{
	if (exp_table == NULL)
		return ;
	if (exp_table->table_len < 2)
		single_exec(exp_table[0], 0);
	else
		pipe_execution(exp_table);
	// print_tables(exp_table);
}
