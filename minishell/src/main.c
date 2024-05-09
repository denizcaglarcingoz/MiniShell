
#include "minishell.h"

static void	loop_items(t_shell *shell)
{
	shell->tokens = build_token_list(shell->input, shell);
	free(shell->input);
	shell->tokens = grammer_check(shell->tokens);
	shell->tables = parser(shell->tokens);
	execution(shell);
}	

void	shell_loop(t_shell *shell)
{
	char		*init_in;

	shell->tables = NULL;
	errno = 0;
	while (1)
	{
		init_in = readline("minishell$ ");
		if (errno != 0 )
			readline_error_exit(init_in, shell);
		if (init_in == NULL)
			break ;
		shell->input = ft_strtrim(init_in, " ");
		if (shell->input == NULL)
			trim_error_exit(init_in, shell);
		if (ft_strcmp(shell->input, "") != 0)
			add_history(init_in);
		free(init_in);
		loop_items(shell);
	}
	control_d_exit(shell);
}
	
int	main(int ac, char **av)
{
	t_shell shell;

	(void)av;
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
	shell.exit_status = 0;
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	shell.env = get_env();
	if (!shell.env)
		exit(EXIT_FAILURE);
	shell.exported = get_env();
	if (!shell.exported)
	{
		free_all_env(shell.env);
		exit(EXIT_FAILURE);
	}
	ft_quicksort_params(shell.exported, 0, ft_matrix_len(shell.exported) - 1);
	//print_intro();
	shell_loop(&shell);
	return (0);
}
