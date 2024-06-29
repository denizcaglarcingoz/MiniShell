/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:50 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/27 22:32:37 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_sig_int;

void	sigint_handler_quit(int signum)
{
	(void)signum;
	printf("Quit (core dumped or did it ;) )\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	kill(g_sig_int, SIGTERM);
	g_sig_int = 5;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)*info;
	(void)context;
}

void	sigint_handler_hdoc(int signum)
{
	(void)signum;
	if (g_sig_int != 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	g_sig_int = 1;
	return ;
}

void	sigint_handler_child(int signum)
{
	(void)signum;
	return ;
}
