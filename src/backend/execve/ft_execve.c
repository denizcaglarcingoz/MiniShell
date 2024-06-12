/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:12 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/12 21:37:04 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_sig_int;

char	**app_assign_new(char **new, char **str, char *path_add)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		new[i] = ft_strjoin(str[i], path_add);
		if (!new[i])
		{
			free_matrix(new, i);
			free(path_add);
			free_d_str(str);
			return (NULL);
		}
	}
	new[i] = NULL;
	return (new);
}

char	**append_path(char **str, char *path_add)
{
	char	**new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char *));
	if (new == NULL)
	{
		free(path_add);
		free_d_str(str);
		return (NULL);
	}
	new = app_assign_new(new, str, path_add);
	if (!new)
		return (NULL);
	free(path_add);
	free_d_str(str);
	return (new);
}

int	path_run_access_check(char **all_paths, char **argv, \
char **environ, t_shell *shell)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (all_paths[++i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0)
		{
			pid = fork();
			if (pid == -1)
				free_d_all(all_paths, "execve fail\n", shell, 127);
			if (pid == 0)
			{
				execve(all_paths[i], argv, environ);
				free_d_all(all_paths, "execve fail\n", shell, 127);
			}
			else
			{
				// wait(NULL);
				get_exit_code(shell, pid);
				free_d_all(all_paths, "no print\n", shell, 0);
				return (1);
			}
		}
	}
	return (0);
}

char	*path_run(char **all_paths, char **argv, char **environ, t_shell *shell)
{
	if (path_run_access_check(all_paths, argv, environ, shell))
		return (NULL);
	write(2, argv[0], ft_strlen(argv[0]));
	if (ft_strlen(argv[0]) > 0)
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
	{
		printf("minishell: %s: Is a directory\n", argv[0]);
		free_all(shell, "no print\n", 126);
		return (NULL);
	}
	if (access(first_arg, X_OK) == 0)
	{
		if (ft_access(first_arg, argv, shell))
			return (wait(NULL), NULL);
	}
	path = ft_getenv("PATH", shell->env);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", argv[0]);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 0);
		return (NULL);
	}
	all_paths = append_path(ft_split(ft_getenv("PATH", shell->env), ':'), \
	ft_strjoin("/", first_arg));//must protect for cases split fail, or split success and join fail.
	if (all_paths == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	return (path_run(all_paths, argv, shell->env, shell));
}
