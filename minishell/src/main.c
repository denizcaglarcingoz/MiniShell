#include "../includes/minishell.h"

void	check_and_run_builtins(t_tokens *tokens, char **env)
{
	if (tokens == NULL)
		return ;
    (void)env;
	// if (ft_strcmp(tokens->content, "exit") == 0) 
	// 	ft_exit(tokens);
	// else if (ft_strcmp(tokens->content, "echo") == 0) //maybe after error check, check builtins, do else
	// 	ft_echo(tokens);
	// else if (ft_strcmp(tokens->content, "cd") == 0) 
	// 	ft_cd(tokens);
	// else if (ft_strcmp(tokens->content, "pwd") == 0) 
	// ft_pwd();
	//function takes any node from list as a start.
	//check command against all builtins here, then against all other cmds in next function, if no match invalid	
}

void	reset_and_run(t_tokens **tokens, char *input)
{
	//RESET FOR NEXT PASS, AND CALL LOOP AGAIN
	free(input);	
	/* print(tokens);
	printf("--------"); */
	if (*tokens != NULL)
		free_list(tokens);
	shell_loop();
}

void	shell_loop()//at completion of execution reset all data and recall this.
{
	char		*init_in;
	char		*input;
	t_tokens	*tokens;
	t_table		*table;

	errno = 0;
	init_in = readline("\001\033[1;94m\002minishell\001\033[1;92m\002$\001\033[0m\002 ");
	if (errno != 0 )
	{
		perror(strerror(errno));
		clear_history();
		free(init_in);
		printf("readline errno: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	input = ft_strtrim(init_in, " ");
	if (input == 0)
	{
		clear_history();
		free(input);
		free(init_in);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(input, "") != 0)
		add_history(init_in);//free/ clear history.(reset) /// to keep up arrow button history add history is necessary // clean at the end
	free(init_in);
	tokens = build_token_list(input);
	// printf("--------\n");//test
	tokens = grammer_check(tokens);
	//print_tokens(tokens);//test
	// tokens = expandor(tokens);
	// print_tokens(tokens);//test
	table = parser(tokens);
	//printf("\n--------\n");//test
	// print_tables(table);
	// printf("\n--------\n");//test
	execution(table);
	//check_and_run_builtins(tokens, env);
	reset_and_run(&(tokens), input);
}

int	main(int ac, char **av, char **envp)
{
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);

	(void)av;
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	if (get_full_env(ft_d_strdup(envp)) == 0)// SHELL STRUCT AND PASS.
		return (printf("Env Malloc Err\n"), EXIT_FAILURE);
	shell_loop();
	return (0);
}
