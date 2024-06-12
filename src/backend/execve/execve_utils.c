/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:09 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/12 17:17:22 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_sig_int;

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	free_d_all(char **all_paths, char *msg, t_shell *shell, int type)
{
	free_d_str(all_paths);
	free_all(shell, msg, type);
}

int	ft_access(char *path, char **argv, t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];
	char	buffer[1024];

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		free_all(shell, "fork failed\n", 127);
	if (pid == 0)
	{
		close(pipefd[0]);
		g_sig_int = getpid();
		write(pipefd[1], ft_itoa(g_sig_int), ft_strlen(ft_itoa(g_sig_int)));
		execve(path, argv, shell->env);
		free_all(shell, "execve failed\n", 127);
	}
	else
	{
		get_exit_code(shell, pid);
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer));
		g_sig_int = ft_atoi(buffer);
		free_all(shell, "no print\n", 3);
		return (1);
	}
	return (0);
}
