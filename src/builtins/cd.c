/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:50 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 23:14:15 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_old(t_shell *shell)
{
	char	*temp;
	char	*old;
	char	*pwd;

	pwd = ft_getenv("PWD", shell->env);
	if (pwd == NULL)
		return (set_nullpwd(shell));
	old = ft_strdup(pwd);
	if (!old)
		return (2);
	temp = ft_strjoin("OLDPWD=", old);
	free(old);
	if (!temp)
		return (2);
	shell->env = add_env(shell->env, temp);
	shell->exported = add_env(shell->exported, temp);
	free(temp);
	if (!shell->env || !shell->exported)
	{
		free_all_env(shell->exported);
		free_all_env(shell->env);
		free_all(shell, "cd add_env", 5);
	}
	return (EXIT_SUCCESS);
}

int	update_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*temp;

	getcwd(cwd, sizeof(cwd));
	temp = ft_strjoin("PWD=", cwd);
	if (!temp)
		return (2);
	shell->env = add_env(shell->env, temp);
	shell->exported = add_env(shell->exported, temp);
	free (temp);
	if (!shell->env || !shell->exported)
		return (2);
	return (0);
}

int	absolute_home(char **full_cmd, t_shell *shell)
{
	char	*path;

	if (!(*(full_cmd + 1)) || !ft_strcmp(full_cmd[1], "~"))
	{
		path = ft_getenv("HOME", shell->env);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (**(full_cmd + 1) == '\0')
		return (EXIT_SUCCESS);
	else if (!ft_strcmp(full_cmd[1], "-"))
	{
		path = ft_getenv("OLDPWD", shell->env);
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	}
	else
		path = full_cmd[1];
	if (chdir(path) == -1)
		return (cd_not_found(path), 1);
	else if (*(full_cmd + 1) && **(full_cmd + 1) == '-')
		cd_dash_putpath(path);
	return (EXIT_SUCCESS);
}

int	handle_relative(char **full_cmd, t_shell *shell)
{
	char	*curr_dir;
	char	*path;

	curr_dir = getcwd(NULL, 0);
	if (!curr_dir && (!ft_strcmp(full_cmd[1], "..")))
	{
		if (handle_twodotempty(shell) == 3)
			return (3);
		return (0);
	}
	else if (!curr_dir && ft_strcmp(full_cmd[1], ".."))
		return (cd_not_found(full_cmd[1]), 1);
	path = malloc(ft_strlen(curr_dir) + ft_strlen(full_cmd[1]) + 2);
	if (!path)
		return (free(curr_dir), 2);
	ft_strcpy(path, curr_dir);
	ft_strcat(path, "/");
	ft_strcat(path, full_cmd[1]);
	free(curr_dir);
	if (chdir(path) == -1)
	{
		cd_not_found(full_cmd[1]);
		return (free(path), 1);
	}
	return (free(path), 0);
}

int	ft_cd(char **full_cmd, t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_matrix_len(full_cmd) > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~' || \
	**(full_cmd + 1) == '/' || **(full_cmd + 1) == '\0' || \
	**(full_cmd + 1) == '-')
	{
		status = absolute_home(full_cmd, shell);
	}
	else
		status = handle_relative(full_cmd, shell);
	if (status == 1)
		return (1);
	if (status == 3)
		return (0);
	if (update_old(shell) || update_pwd(shell) || status == 2)
		free_all(shell, "cd malloc failed", 127);
	return (EXIT_SUCCESS);
}
