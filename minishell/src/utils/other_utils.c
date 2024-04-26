#include "minishell.h"

void	early_error_exit(char *init_in, t_shell *shell)
{
	clear_history();
	if (shell->input)
		free(shell->input);
	free(shell->input);
	free(init_in);
	free_all_env(shell->env);
	free_all_env(shell->exported);///-----------
	ft_putstr_color_fd(2, "Malloc Error", "\033[1;94");
	exit(EXIT_FAILURE);
}