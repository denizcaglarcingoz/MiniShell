/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:26 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 20:11:42 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_list_env(t_shell *shell)
{
	if (shell->env)
		free_all_env(shell->env);
	if (shell->exported)
		free_all_env(shell->exported);
	free_list(shell->tokens);
}

static void	free_all_ops(t_shell *shell, char *print, int exit_type)
{
	if (exit_type == 0)
	{
		free_list(shell->tokens);
		free_table(shell->tables);
		shell->exit_status = 0;
	}
	else if (exit_type == 1)
	{
		shell->exit_status = 1;
		clear_history();
		exit(1);
	}
	else if (exit_type == 126)
	{
		shell->exit_status = 126;
		free_list(shell->tokens);
		free_table(shell->tables);
	}
	else if (exit_type == 2)
	{
		clear_history();
		free_list_env(shell);
		perror(print);
		exit (2);
	}
}

void	free_all(t_shell *shell, char *print, int exit_type)
{
	if (exit_type == 127)
	{
		if (ft_strcmp(print, "no print") != 0)
			perror(print);
		free_list_env(shell);
		clear_history();
		free_table(shell->tables);
		exit(127);
	}
	else
		free_all_ops(shell, print, exit_type);
}
