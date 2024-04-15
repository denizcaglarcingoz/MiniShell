#include "minishell.h"

void	ft_exit(t_tokens *tokens, t_shell *shell, t_table *table)
{
	int code;

	code = 0;
	if (tokens->next)
		code = ft_atoi(tokens->next->content);
	if (code < 0 || code > 255) 
	code = 0;// needs to exit with last code that it had . $?
	
	ft_putstr_color_fd(1, "Exiting MINISHELL!\n", BOLD_GREEN);
	clear_history();
	free(shell->input);
	free_list(&tokens);
	free_all_env(shell->env);
	if (table)
		free_t_content_alloc_and_table(table, shell->table_len);
	printf("exit code: %d\n", code);
	exit(code);
}