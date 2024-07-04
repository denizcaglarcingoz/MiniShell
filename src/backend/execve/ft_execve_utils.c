/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:09 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 01:04:55 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_path_check(char *all_path)
{
	int	i;

	i = 0;
	while (all_path[i])
	{
		if (all_path[i] == '/')
		{
			i++;
			if (all_path[i] == '/')
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

int	dot_check(char *first_arg, t_shell *shell)
{
	if (first_arg[0] == '.' && first_arg[1] == '\0')
	{
		ft_putstr_fd("bash: .: filename argument required\n \
		.: usage: . filename [arguments]\n", 2);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 3);
		return (1);
	}
	if (first_arg[0] == '.' && first_arg[1] == '.'
		&& first_arg[1] != '\0' && first_arg[2] == '\0')
	{
		ft_putstr_fd("..: command not found", 2);
		shell->exit_status = 127;
		free_all(shell, "no print\n", 3);
		return (1);
	}
	return (0);
}

char	*it_is_directory(char *first_arg, t_shell *shell)
{
	if (dot_check(first_arg, shell) == 1)
		return (NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(first_arg, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_all(shell, "no print\n", 126);
	return (NULL);
}
