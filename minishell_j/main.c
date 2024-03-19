#include "minishell.h"


void	reset_and_run(char *input)
{
	//reset
	free(input);	
	//print(tokens);
	//free_list(tokens);
	shell_loop();
}

void	shell_loop()//at completion of execution reset all data and recall this.
{
	char *init_in;
	char *input;
	t_tokens *tokens;

	init_in = readline("\033[1;94mminishell\033[1;92m$\033[0m ");
	if (errno != 0 )
	{
		ft_putstr_color_fd(2, "Malloc Error", "\033[1;94");
		clear_history();
		free(init_in);
		exit(EXIT_FAILURE);
	}
	input = ft_strtrim(init_in, " ");
	if (input == 0)
	{
		clear_history();
		free(input);
		exit(EXIT_FAILURE);
	}
    else if (ft_strncmp(input, "exit", 4) == 0) 
	{
        ft_putstr_color_fd(1, "Exiting MINISHELL!\n", BOLD_GREEN);
		free(input);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(init_in, "", 1) != 0)
		add_history(init_in);//free/ clear history.(reset) /// to keep up arrow button history add history is necessary // clean at the end
	free(init_in);
	tokens = build_token_list(input);
	print_tokens(tokens);
	reset_and_run(input);
}

int	main(int ac, char **av, char **envp)
{
	//t_shell *shell;
	//shell = NULL;
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);

	(void)av;
	(void)envp;
	
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	//print_intro();
	shell_loop();
	return (0);
}

