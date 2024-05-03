#include "minishell.h"

void	free_table(t_table *tables)
{
	int	i;

	i = 0;
	return ;
	while (tables[i].args != NULL)
	{
		free_d_str(tables[i].args);
		free_d_str(tables[i].in);
		free_d_str(tables[i].out);
		free_d_str(tables[i].append);
		free_d_str(tables[i].heredoc);
		i++;
	}
	free(tables);
}

void	free_all(t_table *tables, int all, char *error)
{
	free_table(tables);
	free_list(tables->tokens);
	
	if (all == 1)
	{
		clear_history();
		free_env();
		if (error != NULL)
			perror(error);
		exit(127);
	}
}