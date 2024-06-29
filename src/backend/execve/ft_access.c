/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:07:13 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 14:11:47 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern pid_t	g_sig_int;

void	ft_access_execve(char *path, char **argv, t_shell *shell, int pipefd[2])
{
	close(pipefd[0]);
	g_sig_int = getpid();
	write(pipefd[1], ft_itoa(g_sig_int), ft_strlen(ft_itoa(g_sig_int)));
	close(pipefd[1]);
	execve(path, argv, shell->env);
	free_all(shell, "execve failed\n", 127);
}

int	ft_access(char *path, char **argv, t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];
	char	buffer[1024];
	ssize_t	bytes_read;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		free_all(shell, "fork failed\n", 127);
	if (pid == 0)
		ft_access_execve(path, argv, shell, pipefd);
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_int_exec);
	g_sig_int = pid;
	get_exit_code(shell, pid);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[1]);
	bytes_read = read(pipefd[0], buffer, sizeof(buffer));
	if (bytes_read == -1)
		free_all(shell, "read failed\n", 127);
	buffer[bytes_read] = '\0';
	g_sig_int = ft_atoi(buffer);
	free_all(shell, "no print\n", 3);
	close(pipefd[0]);
	return (1);
}
