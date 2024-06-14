/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:15 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/12 23:11:07 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_list_error_exit(t_shell *shell)
{
	free_list(shell->tokens);
	clear_history();
	free(shell->input);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_fd("Token List Malloc Error\n", 2);
	exit(EXIT_FAILURE);
}

void	readline_error_exit(char *init_in, t_shell *shell)
{
	perror(strerror(errno));
	clear_history();
	free(init_in);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_fd("Readline Errno: ", 2);
	ft_putnbr_fd(errno, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	trim_error_exit(char *init_in, t_shell *shell)
{
	clear_history();
	free(shell->input);
	free(init_in);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	ft_putstr_fd("Strtrim Malloc Error", 2);
	exit(EXIT_FAILURE);
}

void	control_d_exit(t_shell *shell)
{
	clear_history();
	free_all_env(shell->env);
	free_all_env(shell->exported);
	exit(shell->exit_status);
}
