/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:12 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/13 19:58:00 by dcingoz          ###   ########.fr       */
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

int all_path_check(char *all_path)
{
	int i;

	i = 0;
	while (all_path[i])
	{
		if (all_path[i] == '/')
		{
			i++;
			if(all_path[i] == '/')
				return (0);
			if (all_path[i] == '.')
			{
				i++;
				if (all_path[i] == '/')
					return (0);
			}
		}
		i++;
	}
	return (1);
}


int	path_run_access_check(char **all_paths, char **argv, \
char **environ, t_shell *shell)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (all_paths[++i] != NULL)
	{
		if (access(all_paths[i], X_OK) == 0 && ft_strlen(argv[0]) > 0 && all_path_check(all_paths[i]) == 1)
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
				free_d_all(all_paths, "no print\n", shell, 3);
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

int	dot_check(char *first_arg, t_shell *shell)
{
	if (first_arg[0] == '.' && first_arg[1] == '\0')
	{
		ft_putstr_fd("bash: .: filename argument required\n .: usage: . filename [arguments]\n", 2);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 3);
		return (1);
	}
	
	if (first_arg[0] == '.' && first_arg[1] == '.' && first_arg[1] != '\0' && first_arg[2] == '\0')
	{
		ft_putstr_fd("..: command not found", 2);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 3);
		return (1);
	}
	return (0);
}
char	*ft_execve(char *first_arg, char **argv, t_shell *shell)
{
	char	**all_paths;
	char	*path;

	if (argv[0] == NULL)
		return (NULL);
	if (is_directory(first_arg) == 1)
	{
		if (dot_check(first_arg, shell) == 1)
			return (NULL);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(first_arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 3);
		return (NULL);
	}
	all_paths = append_path(ft_split(ft_getenv("PATH", shell->env), ':'), \
	ft_strjoin("/", first_arg));//must protect for cases split fail, or split success and join fail.
	if (all_paths == NULL)
		free_all(shell, "Malloc Fail\n", 127);
	return (path_run(all_paths, argv, shell->env, shell));
}
