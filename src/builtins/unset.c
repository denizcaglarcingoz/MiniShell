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

int	ft_unset(t_table *table, char **full_cmd, t_shell *shell)
{
	int	status;
	int	i;

	(void)table;
	status = 0;
	i = 0;
	if (check_option(&status, full_cmd) == 2)
		return (status);
	while (full_cmd[++i])
	{
		if (ft_getenv(full_cmd[i], shell->env) == NULL && \
		ft_getenv(full_cmd[i], shell->exported) != NULL)
			shell->exported = del_env(shell->exported, full_cmd[i]);
		else if (ft_getenv(full_cmd[i], shell->env) == NULL && \
		ft_getenv(full_cmd[i], shell->exported) == NULL)
			continue ;
		else
		{
			shell->env = del_env(shell->env, full_cmd[i]);
			shell->exported = del_env(shell->exported, full_cmd[i]);
		}
		if (shell->env == NULL || shell->exported == NULL)
			free_all(shell, "unset malloc failed", 127);
	}
	return (status);
}
