/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/07 21:18:33 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_set(int *out_fd, char ***hdoc, t_shell *shell)
{
	char *non_exp_hdoc;

	// if (shell->tables[0].args[0] == NULL)
		// return (free_all(shell, "no print", 3), 1);
	*out_fd = dup(STDOUT_FILENO);
	if (*out_fd == -1)
		free_all(shell, "dup error", 127);
	non_exp_hdoc = get_last_non_exp_hdoc(shell->tables[0], shell);
	if (expandor_hdoc(shell, 0) == false)
		return (close(*out_fd), 1);
	*hdoc = NULL;
	*hdoc = check_hdoc(shell->tables[0], shell);
	if (g_sig_int == SIGUSR1)
	{
		if (non_exp_hdoc != NULL)
			free(non_exp_hdoc);
		close(*out_fd);
		free_all(shell, "no print", 3);
		free(*hdoc);
		signal(SIGINT, sigint_handler_sigint);
		kill(0, SIGINT);
		signal(SIGINT, sigint_handler_int);
		return (1);
	}
	if (*hdoc != NULL)
		*hdoc[0] = hdoc_in_expand(shell, *hdoc[0], non_exp_hdoc);
	if (expandor(shell, 0) == false)
		return (close(*out_fd), 1);
	// if (shell->tables[0].args[0] == NULL)
	// 	return (free_all(shell, "no print", 3), 1);
	return (0);
}

void	no_out_o_arg(t_shell *shell)
{
	int	dup_res;

	dup_res = dup2(shell->out_fd, STDOUT_FILENO);
	if (dup_res == -1)
		free_all(shell, "dup2 error", 127);
	close(shell->out_fd);
	free_all(shell, "no print", 3);
}

void	single_exec(t_shell *shell)
{
	t_single_exec_var	var;
	int					dup_res;

	shell->in_fd = -1;
	shell->out_fd = -1;
	if (check_and_set(&(shell->out_fd), &(var.hdoc), shell))
	{
		return ;}
	var.in = check_in(shell->tables[0]);
	if (shell->tables->in[0] != NULL && var.in == NULL)
	{
		// check for out and append and create those files if necesssary
		// the ones that existed before the non-existing input file
		return (close(shell->out_fd), not_in_file(shell->tables->in, shell));
	}
	var.is_out = output_check(shell->tables[0], 0, shell->tokens);
	if (var.is_out != -1 && shell->tables[0].args[0] == NULL)
		return (no_out_o_arg(shell));
	if (var.is_out == -127)
		return (shell->exit_status = 1, free_all(shell, "no print", 3));
	single_exec_run(shell, &var);
	if (var.is_out != -1)
	{
		dup_res = dup2(shell->out_fd, STDOUT_FILENO);
		if (dup_res == -1)
			free_all(shell, "dup2 error", 127);
	}
	close(shell->out_fd);
}
