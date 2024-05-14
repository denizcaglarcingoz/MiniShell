#include "minishell.h"


void free_all(t_shell *shell, char *print, int exit_type)
{
    if (exit_type == 127)
    {
		if (ft_strcmp(print, "no print") != 0)
	        perror(print);
		clear_history();
        free_d_str(shell->env);
        free_d_str(shell->exported);
        free_list(shell->tokens);
        free_table(shell->tables);
        exit(127);
    }
    else if (exit_type == 0)
    {
        free_list(shell->tokens);
        free_table(shell->tables);
		shell->exit_status = 0;
	}
	else if (exit_type == 1)
	{
		shell->exit_status = 1;
		clear_history();
		exit(1);
	}
	else if (exit_type == 126)
	{
		shell->exit_status = 126;
		free_list(shell->tokens);
        free_table(shell->tables);
	}
}