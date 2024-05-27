
#include "minishell.h"

pid_t sig_int;

void	shell_loop(t_shell *shell)//at completion of execution reset all data and recall this.
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
		/* else
		{
			init_in = get_next_line(fileno(stdin));
		} */
		if (errno != 0 )
			readline_error_exit(init_in, shell);//rename
		if (init_in == NULL)
			break ;
		shell->input = ft_strtrim(init_in, " ");
		if (shell->input == NULL)
			trim_error_exit(init_in, shell);
		if (ft_strcmp(shell->input, "") != 0)
			add_history(init_in);
		free(init_in);
		shell->tokens = build_token_list(shell->input);//mem safe with frees and exit if null.
		free(shell->input);
		shell->tokens = grammer_check(shell->tokens);
		shell->tables = parser(shell->tokens);
		execution(shell);//shell added
	}
	control_d_exit(shell);
}
	//reset_and_run(&tokens, shell, table);

int	main(int ac, char **av)
{
	t_shell shell;
	struct sigaction	sig;
	//int					i;

	//i = 0;
	sig.sa_sigaction = signal_handler;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, 0);
	sig_int = getpid();
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	shell.exit_status = 0;//testing must truly handle exit status
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	shell.env = get_env();
	if (!shell.env)
		exit(EXIT_FAILURE);
	shell.exported = get_env();//(char **)malloc(sizeof(char*));//
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

	///PARSE AND TABLES TESTING-----------------
	/* printf("\n--------\n");//test
	print_tables(table);
	printf("\n--------\n");//test */
	//-------------------------------------