/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:18 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:19 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	check_valid_id(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]) || !(s[i] == '_' || ft_isalpha(s[i])))
		return (1);
	while (s[++i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i])) && !(s[i] == '_'))
			return (1);
	}
	return (0);
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i] != NULL)
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j] != '=' && env[i][j])
			ft_putchar_fd(env[i][j], 1);
		if (env[i][j] != '\0')
		{
			ft_putchar_fd(env[i][j], 1);
			ft_putchar_fd('\"', 1);
			while (env[i][++j])
			{
				if (env[i][j] == '\"')
					ft_putchar_fd('\\', 1);
				ft_putchar_fd(env[i][j], 1);
			}
			ft_putchar_fd('\"', 1);
		}
		ft_putstr_fd("\n", 1);
	}
}

int	export_loop(char *cmd, t_shell *shell)
{
	int	ret;	

	ret = 0;
	if (check_valid_id(cmd))
		ret = invalid_id(cmd);
	else if (!has_equal(cmd))
	{
		shell->exported = add_env(shell->exported, cmd);
		ft_quicksort_params(shell->exported, 0, \
		ft_matrix_len(shell->exported) - 1);
	}
	else
	{
		shell->env = add_env(shell->env, cmd);
		shell->exported = add_env(shell->exported, cmd);
		ft_quicksort_params(shell->exported, 0, \
		ft_matrix_len(shell->exported) - 1);
	}
	if (shell->env == NULL || shell->exported == NULL)
		ret = 2;
	return (ret);
}

int	ft_export(char **full_cmd, t_shell *shell)
{
	int		i;
	int		status;

	status = 0;
	if (!(*(full_cmd + 1)))
		print_export(shell->exported);
	else
	{
		i = 0;
		while (full_cmd[++i])
		{
			status = export_loop(full_cmd[i], shell);
			if (status == 2)
				free_all(shell, "export malloc failed", 127);
		}
	}
	return (status);
}
