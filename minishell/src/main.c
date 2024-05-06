
#include "minishell.h"

void	reset(t_table *table)
{
	//free_t_content_alloc_and_table(table, shell->table_len);
	//free(shell->input);	
	if (table->tokens != NULL)
		free_list(table->tokens);
	free_table(table);
	//shell->table_len = 0;
	//shell_loop(shell);
}

void	shell_loop(t_shell *shell)//at completion of execution reset all data and recall this.
{
	char		*init_in;
	t_tokens	*tokens;
	t_table 	*table;

	table = NULL;
	errno = 0;
	while (1)
	{
		init_in = readline("minishell$ ");
		//init_in = readline("\033[1;94mminishell\033[1;92m$\033[0m "); issue with col?
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
		tokens = build_token_list(shell->input);//mem safe with frees and exit if null.
		free(shell->input);
		tokens = grammer_check(tokens);
		table = parser(tokens);//redo mem safe. 
		table = execution(table, shell);//shell added
		//if (tokens == NULL)
		//	ft_exit(table, );		
		//free_list(&tokens); //free here?
		if (tokens != NULL)
			reset(table);
	}
	control_d_exit(shell);
}
	//reset_and_run(&tokens, shell, table);

int	main(int ac, char **av)
{
	t_shell shell;

	(void)av;
	signal(SIGINT, sigint_handler_int);
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