/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:12 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 11:22:49 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_path_run_child_clean(t_shell *shell)
{
	signal(SIGQUIT, sigint_handler_quit);
	if (shell->in_fd != -1)
		close(shell->in_fd);
	if (shell->out_fd != -1)
		close(shell->out_fd);
}

int	path_run_access_check(char **all_paths, char **argv, \
char **environ, t_shell *shell)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (all_paths[++i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0
			&& ft_strlen(argv[0]) > 0 && all_path_check(all_paths[i]) == 1)
		{
			pid = fork();
			if (pid == -1)
				free_d_all(all_paths, "execve fail\n", shell, 127);
			if (pid == 0)
			{
				s_path_run_child_clean(shell);
				execve(all_paths[i], argv, environ);
				free_d_all(all_paths, "execve fail\n", shell, 127);
			}
			path_run_signals(pid, shell);
			return (free_d_all(all_paths, "", shell, 3), 1);
		}
	}
	return (0);
}

int	permission_denied(char *path, t_shell *shell, char **all_paths)
{
	if (access(path, X_OK) != 0 && path[0] == '.' && path[1] == '/')
	{
		if (access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			free_d_all(all_paths, "no print\n", shell, 0);
			shell->exit_status = 127;
			return (1);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_d_all(all_paths, "no print\n", shell, 0);
		shell->exit_status = 126;
		return (1);
	}
	return (0);
}

char	*path_run(char **all_paths, char **argv, char **environ, t_shell *shell)
{
	int	permission;

	if (path_run_access_check(all_paths, argv, environ, shell))
		return (NULL);
	permission = permission_denied(argv[0], shell, all_paths);
	if (permission == 1)
		return (NULL);
	write(2, argv[0], ft_strlen(argv[0]));
	if (argv[0] != NULL)
		write(2, ": command not found\n", 20);
	free_d_all(all_paths, "no print\n", shell, 0);
	shell->exit_status = 127;
	return (NULL);
}

char	*ft_execve(char *first_arg, char **argv, t_shell *shell)
{
	char	**all_paths;
	char	*path;

	if (argv[0] == NULL)
		return (NULL);
	if (is_directory(first_arg) == 1)
		return (it_is_directory(first_arg, shell));
	if (access(first_arg, X_OK) == 0)
		if (ft_access(first_arg, argv, shell))
			return (wait(NULL), NULL);
	path = ft_getenv("PATH", shell->env);
	if (path == NULL)
		return (null_path(argv[0], shell), NULL);
	all_paths = append_path(ft_split(ft_getenv("PATH", shell->env), ':'), \
	ft_strjoin("/", first_arg));
	if (all_paths == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	return (path_run(all_paths, argv, shell->env, shell));
}
