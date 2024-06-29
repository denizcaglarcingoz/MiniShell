/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:50 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/27 22:32:26 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_sig_int;

void	sigint_handler_int(int signum)
{
	(void)signum;
	if (g_sig_int == 0)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sigint_handler_int_exec(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
