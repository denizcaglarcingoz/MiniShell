/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:07:13 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/03 06:23:12 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_access_execve(char *path, char **argv, t_shell *shell)
{
	signal(SIGQUIT, sigint_handler_quit);
	execve(path, argv, shell->env);
	free_all(shell, "execve failed\n", 127);
}

int	ft_access(char *path, char **argv, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		free_all(shell, "fork failed\n", 127);
	if (pid == 0)
		ft_access_execve(path, argv, shell);
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_int_exec);
	get_exit_code(shell, pid);
	signal(SIGQUIT, SIG_IGN);
	free_all(shell, "no print\n", 3);
	return (1);
}
