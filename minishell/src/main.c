
#include "minishell.h"

int	check_and_run_builtins_2(t_table *table, char **full_cmd, t_shell *shell)
{ 
	(void)table;
	if (ft_strcmp(full_cmd[0], "pwd") == 0)//prints cannot fail.
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strcmp(full_cmd[0], "env") == 0)//env only prints, cannot fail
	{
		print_env(shell->env);
		return (1);
	}
	else if (ft_strcmp(full_cmd[0], "echo") == 0)//env only prints, cannot fail
	{
		ft_echo(full_cmd);
		return (1);
	}
	return (0);
}

int	check_and_run_builtins(t_table *table, char **full_cmd, t_shell *shell)
{
	
//	if (**full_cmd == '$')//handle with dollar sign. receives expanded already.
//		parse_dollar(table, shell);
	if (ft_strcmp(full_cmd[0], "exit") == 0) 
		ft_exit(table, full_cmd, shell);//maybe set equal to stat and determine exit status
	else if (ft_strcmp(full_cmd[0], "cd") == 0) 
		ft_cd(full_cmd, shell);//malloc fail returns 2, fail to find 1, 0 good;
	else if (ft_strcmp(full_cmd[0], "export") == 0)
	{
		ft_export(full_cmd, shell);
		return (2);
	}
	else if (ft_strcmp(full_cmd[0], "unset") == 0)
	{
		ft_unset(table, full_cmd, shell);
		return (2);
	}
	if ((ft_strcmp(full_cmd[0], "cd") == 0) || (ft_strcmp(full_cmd[0], "exit") == 0))//export and unset, exit, cd.
		return (2);
	return (0);
	//else check against other commands if non exist then print not a commandif command not found updated shell->exit_status	
}

void	reset_and_run(t_tokens **tokens, t_shell *shell, t_table *table)
{
	free_t_content_alloc_and_table(table, shell->table_len);
	free(shell->input);	
	if (*tokens != NULL)
		free_list(tokens);
	shell->table_len = 0;
	shell_loop(shell);
}

void	shell_loop(t_shell *shell)//at completion of execution reset all data and recall this.
{
	char		*init_in;
	t_tokens	*tokens;
	t_table 	*table;

	table = NULL;
	init_in = readline("\033[1;94mminishell\033[1;92m$\033[0m ");
	if (errno != 0 )
		early_error_exit(init_in, shell);
	shell->input = ft_strtrim(init_in, " ");
	if (shell->input == NULL)
		early_error_exit(init_in, shell);
	if (ft_strcmp(shell->input, "") != 0)
		add_history(init_in);
	free(init_in);
	tokens = build_token_list(shell->input);//mem safe with frees and exit if null.
	//if (tokens == NULL)
	//	ft_exit(table, );		
	tokens = grammer_check(tokens);
	if (tokens == NULL)
		reset_and_run(&tokens, shell, table);
	table = parser(tokens, shell);//redo mem safe. exit has changed clear on null return
	free_list(&tokens); //free here

	///PARSE AND TABLES TESTING-----------------
	printf("\n--------\n");//test
	print_tables(table);
	printf("\n--------\n");//test
	//-------------------------------------
	
	executor(table, shell);// testing the executor here.. not totally fin.
	
	//EXPANDER TESTING-----------------------------------------------------------------------
		//char *exp = expander(tokens->content, shell); //basic version is working, must remove exraneous quotes when needed
	//printf("%s\n", exp);
	//free(exp);
	//printf("|");
	//-----------------------------------------------------------------------------
	reset_and_run(&tokens, shell, table);
}

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
	shell.exported = (char **)malloc(sizeof(char*));//
	if (!shell.exported)
	{
		free_all_env(shell.env);
		exit(EXIT_FAILURE);
	}

	//print_intro();
	shell_loop(&shell);
	return (0);
}

/* 	 shell.env = add_env(shell.env, "here=here");
	// shell.env = add_env(shell.env, "here2=here2");
	shell.env = del_env(shell.env, "he");  */
	// size_t len = get_expanded_len("here is $? stuff $HOME", &shell);//test
	//printf("\n");
	//printf("exp len: %zu\n", len);
	//printf("act len: %zu\n", ft_strlen("here is 12 stuff /home/jhotchki"));

/* void	free_all(t_shell *shell)
{

}
	t_shell shell; */


	//print_tokens(tokens);//test
	//printf("--------\n");//test

//	ft_putstr_color_fd(2, "here", BLUE);
	//print_env(shell.env);
/* void	parse_dollar(t_table *table, char **full_cmd, t_shell *shell)
{
	char *path;
	DIR *dir;

	dir = NULL;
	if (*(tokens->content + 1))
	{
		path = getenv((tokens->content) + 1);//handle if in dquotes
		if (path)
			dir = opendir(path);	
	}
	if (dir)//handling $input MAKE SO ONLY WORKS FOR DIRECTORIES.., now need to handle $PATH, $USER, etc
	{
		printf(MAGENTA"minishell: %s Is a directory\n"RESET, path);
		closedir(dir);
	}
	else if (ft_strcmp(tokens->content + 1, "USER") == 0)
		printf(RED"%s: command not found\n"RESET, path);
	else if ((tokens->content + 1) && tokens->next)
	{
		tokens = tokens->next;
		check_and_run_builtins(tokens, shell, table);
	}
	else
	{	
		if (!(*(tokens->content) == '$' && *(tokens->content + 1)))
			printf(RED"%s: command not found\n"RESET, tokens->content);
	}
} */