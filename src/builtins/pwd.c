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

void	cd_dash_putpath(char *path)
{
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

int	set_nullpwd(t_shell *shell)
{
	if (ft_getenv("OLDPWD", shell->env))
	{
		shell->exported = del_env(shell->exported, "OLDPWD");
		shell->env = del_env(shell->env, "OLDPWD");
		if (!shell->env || !shell->exported)
			return (2);
		shell->exported = add_env(shell->exported, "OLDPWD");
		if (!shell->exported)
			return (2);
	}
	return (0);
}
