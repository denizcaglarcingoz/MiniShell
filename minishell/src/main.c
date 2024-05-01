#include "minishell.h"

void	reset(t_table *table, char *input)
{
	//RESET ALL DATA
	free(input);
	if (table->tokens != NULL)
		free_list(table->tokens);
	free_table(table);
}

void	shell()//at completion of execution reset all data and recall this.
{
	char		*init_in;
	char		*input;
	t_tokens	*tokens;
	t_table		*table;

	errno = 0;
	while (1)
	{
		init_in = readline("minishell$ ");
		if (errno != 0)
		{
			perror(strerror(errno));
			clear_history();
			free(init_in);
			printf("readline errno: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if (init_in == NULL)
			break ;
		input = ft_strtrim(init_in, " ");
		if (input == 0)
		{
			clear_history();
			free_env();
			free(init_in);
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(input, "") != 0)
			add_history(init_in);
		free(init_in);
		tokens = build_token_list(input);
		tokens = grammer_check(tokens);
		table = parser(tokens);
		table = execution(table);
		if (tokens != NULL)
			reset(table, input);
	}
	printf("ctrl d exit\n");
	clear_history();
	free_env();
	exit(EXIT_SUCCESS);
}
	// print_tokens(tokens);//test
	// print_tables(table);

int	main(int ac, char **av, char **envp)
{
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
	char **env;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	env = ft_d_strdup(envp);
	if (env == NULL)
		return (printf("Env Malloc Err\n"), EXIT_FAILURE);
	get_full_env(env);
	shell();
	return (0);
}
