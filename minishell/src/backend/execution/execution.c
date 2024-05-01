#include "minishell.h"
char **check_hdoc(t_table table)
{
	int i;
	char *hdoc;
	char **hdocs;

	if (table.heredoc[0] == NULL)
		return (NULL);
	i = 0;
	hdoc = NULL;
	while (table.heredoc[i] != NULL)
	{
		if (hdoc != NULL)
			free(hdoc);
		hdoc = hdoc_inp((table.heredoc)[i]); // hdoc_inp is a function that is inside of redirections heredoc
		i++;
	}
	hdocs = (char **)malloc(sizeof(char *) * 2);
	hdocs[0] = hdoc;
	hdocs[1] = NULL;
	return (hdocs);
}

char *check_in(t_table table)
{
	int i;
	
	if (table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (table.in[i] != NULL)
	{
		if (access(table.in[i], F_OK) == -1)
			return (NULL);
		i++;
	}
	return (table.in[i - 1]);
}

int	execution(t_table *table)
{
	int error_check;

	error_check = 0;
	if (table == NULL)
		return (0);
	if (table->table_len < 2)
		error_check = single_exec(table);
	else
		error_check = pipe_execution(table);
	
	return (error_check);
	// print_tables(table);
}
