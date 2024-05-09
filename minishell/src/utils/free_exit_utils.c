#include "minishell.h"

void	token_list_error_exit(t_shell *shell)
{
	free_list(shell->tokens);
	clear_history();
	free(shell->input);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_color_fd(2, "Token List Malloc Error\n", BOLD_RED);
	exit(EXIT_FAILURE);
}

void	readline_error_exit(char *init_in, t_shell *shell)
{
	perror(strerror(errno));
	clear_history();
	free(init_in);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	printf("Readline Errno: %d\n", errno);
	exit(EXIT_FAILURE);
}

void	trim_error_exit(char *init_in, t_shell *shell)
{
	clear_history();
	free(shell->input);
	free(init_in);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_color_fd(2, "Strtrim Malloc Error", BOLD_RED);
	exit(EXIT_FAILURE);
}

void	control_d_exit(t_shell *shell)
{
	clear_history();
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_color_fd(1, "CTRL D Exit\n", BOLD_GREEN);
	exit(EXIT_SUCCESS);
}