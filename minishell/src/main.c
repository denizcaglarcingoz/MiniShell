//doing a git test..
#include "minishell.h"

void	sham_parse(t_tokens *tokens)//life is a scam...
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
		ft_putstr_color_fd(1, "minishell: ", MAGENTA);
		ft_putstr_color_fd(1, path, GREEN);
		ft_putstr_color_fd(1, " Is a directory\n", MAGENTA);
		closedir(dir);
	}
	else if (ft_strcmp(tokens->content + 1, "USER") == 0)
	{
		ft_putstr_color_fd(1, path, RED);
		ft_putstr_color_fd(1, ": command not found\n", RED);
	}
	else if ((tokens->content + 1) && tokens->next)
	{
		tokens = tokens->next;
		check_and_run_builtins(tokens);
	}
	else
	{	
		if (!(*(tokens->content) == '$' && *(tokens->content + 1)))
		{
			ft_putstr_color_fd(1, tokens->content, RED);
			ft_putstr_color_fd(1, ": command not found\n", RED);
		}
	}
}

void	check_and_run_builtins(t_tokens *tokens)
{
    //(void)env;
	if (*(tokens->content) == '$')//handle with dollar sign.
		sham_parse(tokens);
	else if (ft_strcmp(tokens->content, "exit") == 0) 
		ft_exit(tokens);
	else if (ft_strcmp(tokens->content, "echo") == 0) // check builtins, check error /path, rerun under correct conditions( SHAM PARSING..)
		ft_echo(tokens);
	else if (ft_strcmp(tokens->content, "cd") == 0) 
		ft_cd(tokens);
	else if (ft_strcmp(tokens->content, "pwd") == 0) 
		ft_pwd();
	else
	{
		if (!(*(tokens->content) == '$' && *(tokens->content + 1)))
		{
			ft_putstr_color_fd(1, tokens->content, RED);
			ft_putstr_color_fd(1, ": command not found\n", RED);
		}
	}
	//else check against other commands if non exist then print not a command
	//function takes any node from list as a start.
	//check command against all builtins here, then against all other cmds in next function, if no match invalid	
}


void	reset_and_run(t_tokens **tokens, char *input, char **env)
{
	//RESET FOR NEXT PASS, AND CALL LOOP AGAIN
	(void)env;
	free(input);	
	/* print(tokens);
	printf("--------"); */
	free_list(tokens);
	shell_loop(env);
}

void	shell_loop(char **env)//at completion of execution reset all data and recall this.
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
		free(init_in);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(input, "") != 0)
		add_history(init_in);//free/ clear history.(reset) /// to keep up arrow button history add history is necessary // clean at the end
	free(init_in);
	tokens = build_token_list(input);
	//print_tokens(tokens);//test
	//printf("--------\n");//test
	check_and_run_builtins(tokens);
	reset_and_run(&tokens, input, env);
}

int	main(int ac, char **av, char **envp)
{
	char **env;
	//t_shell *shell;
	//shell = NULL;
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);

	env = get_env();// SHELL STRUCT AND PASS.
	(void)av;
	(void)envp;
	
	if (ac != 1)
	{
		ft_putstr_color_fd(2, "./minishell takes no arguments\n", "\033[1;91m");
		exit(EXIT_FAILURE);
	}
	//print_intro();
	shell_loop(env);
	return (0);
}

