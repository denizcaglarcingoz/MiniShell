/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:16 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 03:35:46 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pipe_append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (path_add == NULL)
		return (NULL);
	while (str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char *));
	if (new == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		i++;
	}
	new[i] = NULL;
	free(path_add);
	return (new);
}

void	pipe_path_run(char **all_paths, char **argv, char **environ, \
t_shell *shell)
{
	int		i;

	i = 0;
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0
			&& all_path_check(all_paths[i]) == 1)
		{
			signal(SIGQUIT, sigint_handler_quit);
			execve(all_paths[i], argv, environ);
			free_d_str(all_paths);
			free_all(shell, "Pipe Execve Error\n", 127);
		}
		i++;
	}
	write(2, argv[0], ft_strlen(argv[0]));
	if (argv[0] != NULL)
		write(2, ": command not found\n", 20);
	free_d_str(all_paths);
	free_all(shell, "no print", 127);
}

void	null_path(char *argv, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
	if (shell->table_len > 1)
		free_all(shell, "no print", 127);
	if (shell->table_len == 1)
		free_all(shell, "no print", 3);
}

void	ft_pipe_execve(char *path, char **argv, t_shell *shell)
{
	char	**all_paths;
	char	**paths;
	char	*env;

	if (argv[0] == NULL)
		return ;
	if (is_directory(path) == 1)
	{
		printf("minishell: %s: Is a directory\n", argv[0]);
		free_all(shell, "no print\n", 126);
		exit(126);
	}
	if (access(path, X_OK) == 0)
		ft_access_execve(path, argv, shell);
	env = ft_getenv("PATH", shell->env);
	if (env == NULL)
		return (null_path(argv[0], shell));
	paths = ft_split(env, ':');
	all_paths = pipe_append_path(paths, ft_strjoin("/", path));
	free_d_str(paths);
	if (all_paths == NULL)
		free_all(shell, "All Paths Malloc Error\n", 127);
	pipe_path_run(all_paths, argv, shell->env, shell);
}
