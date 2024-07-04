/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:50 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 15:53:45 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit (core dumped or did it ;) )\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigint_handler_hdoc(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	kill(0, SIGUSR1);
	return ;
}

void	sigint_handler_child(int signum)
{
	(void)signum;
	return ;
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	(exit(1));
}
