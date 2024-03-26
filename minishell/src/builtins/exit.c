#include "../../includes/minishell.h"

void	ft_exit(t_tokens *tokens)
{
	int code;

	code = 0;
	if (tokens->next)
		code = ft_atoi(tokens->next->content);
	if (code < 0 || code > 255) 
	code = 0;// needs to exit with last code that it had . $?
	
	ft_putstr_color_fd(1, "Exiting MINISHELL!\n", BOLD_GREEN);
	clear_history();
	free_list(&tokens);
	exit(code);
}