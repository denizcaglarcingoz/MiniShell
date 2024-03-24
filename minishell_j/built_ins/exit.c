#include "../minishell.h"

void	ft_exit(t_tokens *tokens)
{
    ft_putstr_color_fd(1, "Exiting MINISHELL!\n", BOLD_GREEN);
	clear_history();
	free_list(&tokens);
	exit(EXIT_SUCCESS);
}