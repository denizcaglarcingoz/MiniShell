/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:50 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/13 14:29:52 by dcingoz          ###   ########.fr       */
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
		return (0);
	old = ft_strdup(pwd);
	if (!old)
		return (2);
	temp = ft_strjoin("OLDPWD=", old);
	free(old);
	if (!temp)
		return (2);
	shell->env = add_env(shell->env, temp);
	free(temp);
	if (!shell->env)
	{
		free_all_env(shell->exported);
		free_all(shell, "cd add_env", 5);
	}
	return (EXIT_SUCCESS);
}

int	update_pwd(t_shell *shell)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*temp1;

	i = -1;
	getcwd(cwd, sizeof(cwd));
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			temp1 = ft_strjoin("PWD=", cwd);
			if (!temp1)
				return (2);
			free(shell->env[i]);
			shell->env[i] = temp1;
		}
	}
	return (0);
}

int	absolute_home(char **full_cmd, t_shell *shell)
{
	char	*path;

	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~' \
		|| **(full_cmd + 1) == '\0')
		path = ft_getenv("HOME", shell->env);
	else if (**(full_cmd + 1) == '-')
	{
		path = ft_getenv("OLDPWD", shell->env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	else
		path = full_cmd[1];
	if (chdir(path) == -1)
	{
		cd_not_found(full_cmd);
		return (1);
	}
	return (EXIT_SUCCESS);
}

int	handle_relative(char **full_cmd)
{
	char	*curr_dir;
	char	*path;

	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (2);
	path = malloc(ft_strlen(curr_dir) + ft_strlen(full_cmd[1]) + 2);
	if (!path)
	{
		free(curr_dir);
		return (2);
	}
	ft_strcpy(path, curr_dir);
	ft_strcat(path, "/");
	ft_strcat(path, full_cmd[1]);
	free(curr_dir);
	if (chdir(path) == -1)
	{
		cd_not_found(full_cmd);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_cd(char **full_cmd, t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_matrix_len(full_cmd) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~' \
		|| **(full_cmd + 1) == '/' || **(full_cmd + 1) == '\0' \
			|| **(full_cmd + 1) == '-')
	{
		status = absolute_home(full_cmd, shell);
	}
	else
		status = handle_relative(full_cmd);
	if (status == 1)
		return (1);
	if (update_old(shell) || update_pwd(shell) || status == 2)
		free_all(shell, "cd malloc failed", 127);
	return (EXIT_SUCCESS);
}
