#include "minishell.h"

pid_t	g_sig_int;

static void	loop_items(t_shell *shell, char *init_in)
{
	shell->input = ft_strtrim(init_in, " ");
	if (shell->input == NULL)
		trim_error_exit(init_in, shell);
	if (ft_strcmp(shell->input, "") != 0)
		add_history(init_in);
	free(init_in);
	init_in = NULL;
	shell->tokens = build_token_list(shell->input, shell);
	free(shell->input);
	shell->input = NULL;
	shell->tokens = grammer_check(shell->tokens);
	shell->tables = parser(shell->tokens, shell);
	/* if (shell->tables && shell->tables->args)
	{
		if (shell->tables->args[0] \
		&& !ft_strcmp(shell->tables->args[0], "env"))
			shell->env = add_env(shell->env, "_=/usr/bin/env");
	} */
	execution(shell);
	/* if (shell->update_cmd)
		update_last_cmd(shell->update_cmd, shell); */
}

void	shell_loop(t_shell *shell)
{
	char		*init_in;

	shell->tables = NULL;
	errno = 0;
	while (1)
	{
		signal(SIGINT, sigint_handler_int);
		signal(SIGINT, sigint_handler_int);
		if (isatty(fileno(stdin)))
			init_in = readline("minishell$ ");
		else
		{
			errno = 0;
			init_in = get_next_line(fileno(stdin));
		}
		if (errno != 0)
			readline_error_exit(init_in, shell);
		if (init_in == NULL)
			break ;
		loop_items(shell, init_in);
	}
	control_d_exit(shell);
}

int	main(int ac, char **av)
{
	t_shell				shell;
	struct sigaction	sig;

	sig.sa_sigaction = signal_handler;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, 0);
	g_sig_int = getpid();
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", BOLD_RED);
		exit(EXIT_FAILURE);
	}
	init_env(&shell);
	//print_intro();
	shell_loop(&shell);
	return (0);
}

	///PARSE AND TABLES TESTING-----------------
/* 	printf("\n--------\n");//test
	print_tables(shell->tables);
	printf("\n--------\n");//test */
	//-------------------------------------