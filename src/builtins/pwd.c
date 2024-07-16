/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:26 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;
	char	*pwd_str;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_str = ft_getenv("PWD", shell->env);
		if (!pwd_str)
			pwd_str = "\0";
		ft_putstr_fd(pwd_str, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	ft_putstr_fd(cwd, 1);
	free(cwd);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	handle_twodotempty(t_shell *shell)
{
	char	*old;

	old = ft_getenv("OLDPWD", shell->env);
	if (!old)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: can"
			"not access parent directories:"
			" No such file or directory\n", 2);
		return (3);
	}
	else if (chdir(old) == -1)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: can"
			"not access parent directories:"
			" No such file or directory\n", 2);
		return (3);
	}
	return (0);
}
