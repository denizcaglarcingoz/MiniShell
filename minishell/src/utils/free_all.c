#include "minishell.h"


void free_all(t_shell *shell, char *print, int exit_type)
{
	if (exit_type == 127)
    {
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
    }
}