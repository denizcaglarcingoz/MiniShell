/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:33 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:34 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_equal_case(t_shell *shell, char *var)
{
	shell->env = add_env(shell->env, var);
	if (shell->env == NULL)
	{
		free_all_env(shell->exported);
		return (2);
	}
	shell->exported = add_env(shell->exported, var);
	if (shell->exported == NULL)
	{
		free_all_env(shell->env);
		return (2);
	}
	ft_quicksort_params(shell->exported, 0, \
	ft_matrix_len(shell->exported) - 1);
	return (0);
}

static int	check_option(int *status, char **full_cmd)
{
	if (full_cmd[1] && full_cmd[1][0] == '-' && full_cmd[1][1])
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(full_cmd[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		*status = 2;
		return (2);
	}
	return (0);
}

static void	env_and_exp_case(t_shell *shell, char *cmd)
{
	shell->env = del_env(shell->env, cmd);
	if (shell->env == NULL)
	{
		free_all_env(shell->exported);
		free_all(shell, "unset malloc failed", 5);
	}
	shell->exported = del_env(shell->exported, cmd);
	if (shell->exported == NULL)
	{
		free_all_env(shell->env);
		free_all(shell, "unset malloc failed", 5);
	}
}

static void	env_not_exp_case(t_shell *shell, char *cmd)
{
	shell->exported = del_env(shell->exported, cmd);
	if (shell->exported == NULL)
	{
		free_all_env(shell->env);
		free_all(shell, "unset malloc failed", 5);
	}
}

int	ft_unset(char **full_cmd, t_shell *shell)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (check_option(&status, full_cmd) == 2)
		return (status);
	while (full_cmd[++i])
	{
		if (ft_getenv(full_cmd[i], shell->env) == NULL \
		&& ft_getenv(full_cmd[i], shell->exported) != NULL)
			env_not_exp_case(shell, full_cmd[i]);
		else if (ft_getenv(full_cmd[i], shell->env) == NULL \
		&& ft_getenv(full_cmd[i], shell->exported) == NULL)
			continue ;
		else
			env_and_exp_case(shell, full_cmd[i]);
	}
	return (status);
}
