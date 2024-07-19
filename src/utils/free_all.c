/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:26 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 12:07:08 by dcingoz          ###   ########.fr       */
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

void	close_std_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static void	free_all_ops2(t_shell *shell, char *print, int exit_type)
{
	close_std_fd();
	if (exit_type == 2)
	{
		rl_clear_history();
		free_list_env(shell);
		perror(print);
		exit (2);
	}
	else if (exit_type == 4)
	{
		if (ft_strcmp(print, "no print") != 0)
			perror(print);
		rl_clear_history();
		free_list_env(shell);
		exit(2);
	}
	else if (exit_type == 5)
	{
		if (ft_strcmp(print, "no print") != 0)
			perror(print);
		rl_clear_history();
		free_list(shell->tokens);
		free_table(shell->tables);
		exit(1);
	}
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
		rl_clear_history();
		free_list_env(shell);
		free_table(shell->tables);
		close_std_fd();
		exit(1);
	}
	else if (exit_type == 126)
	{
		shell->exit_status = 126;
		free_list(shell->tokens);
		free_table(shell->tables);
	}
	else if (exit_type == 3)
		(free_list(shell->tokens), free_table(shell->tables));
	else
		free_all_ops2(shell, print, exit_type);
}

void	free_all(t_shell *shell, char *print, int exit_type)
{
	if (exit_type == 127)
	{
		if (ft_strcmp(print, "no print") != 0)
			perror(print);
		rl_clear_history();
		free_list_env(shell);
		free_table(shell->tables);
		close_std_fd();
		exit(127);
	}
	else if (exit_type == -1)
	{
		rl_clear_history();
		free_list_env(shell);
		free_table(shell->tables);
		close_std_fd();
		exit(0);
	}
	else
		free_all_ops(shell, print, exit_type);
}
