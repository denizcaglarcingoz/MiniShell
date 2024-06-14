/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:24:46 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 16:23:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	shell->tokens = build_token_list(shell->input, shell);
	// print_tokens(shell->tokens);
	free(shell->input);
	shell->input = NULL;
	shell->tokens = grammer_check(shell->tokens, &shell->exit_status);
	shell->tables = parser(shell->tokens, shell);
	execution(shell);
}

void	shell_loop(t_shell *shell)
{
	char		*init_in;
	extern int	errno;

	shell->tables = NULL;
	while (1)
	{
		signal(SIGINT, sigint_handler_int);
		signal(SIGINT, sigint_handler_int);
		errno = 0;
		init_in = NULL;
		if (isatty(fileno(stdin)))
		{	
			init_in = readline("minishell$ ");
		}
		else
		{
			errno = 0;
			char *line;
			line = get_next_line(fileno(stdin));
			if (line != 0)
				init_in = ft_strtrim(line, "\n");
			free(line);
		}
		if (errno == 4)
			errno = 0;
		if (errno != 0)
			readline_error_exit(init_in, shell);
		if (init_in == NULL)
			break ;
		//  printf("init_in: %s\n", init_in);
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
		ft_putstr_fd("./minishell takes no arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	init_env(&shell);
	shell_loop(&shell);
	return (0);
}

	///PARSE AND TABLES TESTING-----------------
/* 	printf("\n--------\n");//test
	print_tables(shell->tables);
	printf("\n--------\n");//test */
	//-------------------------------------