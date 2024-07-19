/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:24:46 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 10:17:02 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_sig_int;

void	trims(char **init_in, t_shell *shell)
{
	shell->input = ft_strtrim(*init_in, " ");
	if (shell->input == NULL)
		trim_error_exit(*init_in, shell);
}

static void	loop_items(t_shell *shell, char *init_in)
{
	trims(&init_in, shell);
	if (ft_strcmp(shell->input, "") != 0)
		add_history(init_in);
	free(init_in);
	shell->tokens = NULL;
	shell->tokens = build_token_list(shell->input, shell);
	free(shell->input);
	shell->input = NULL;
	shell->tokens = token_content_check(shell->tokens, &shell->exit_status);
	shell->tokens = grammer_check(shell->tokens, &shell->exit_status);
	shell->tables = parser(shell->tokens, shell);
	execution(shell);
}

// static void	else_isatty(char **init_in)
// {
// 	char	*line;

// 	errno = 0;
// 	line = get_next_line(fileno(stdin));
// 	if (line != 0)
// 		*init_in = ft_strtrim(line, "\n");
// 	free(line);
// }
// if (isatty(fileno(stdin)))
// else
	// else_isatty(&init_in);

void	shell_loop(t_shell *shell)
{
	char		*init_in;
	extern int	errno;

	shell->tables = NULL;
	shell->hdoc = NULL;
	while (1)
	{
		signal(SIGINT, sigint_handler_sigint);
		kill(shell->pid, SIGINT);
		signal(SIGINT, sigint_handler_int);
		errno = 0;
		init_in = NULL;
		init_in = readline("minishell$ ");
		if (errno == 4)
			errno = 0;
		if (errno != 0)
			readline_error_exit(init_in, shell);
		if (init_in == NULL)
			break ;
		loop_items(shell, init_in);
	}
	control_d_exit(shell, init_in);
}

int	main(int ac, char **av)
{
	t_shell				shell;

	ft_putstr_fd("Bash by Shell of MiniTeam\n", 1);
	shell.pid = ft_pid(NULL) - 1;
	signal(SIGPIPE, sigpipe_handler);
	signal(SIGUSR1, sigusr1_handler);
	shell.pipe_hdoc_sig = 0;
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
