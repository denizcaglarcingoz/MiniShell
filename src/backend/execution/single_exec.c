/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 14:10:37 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern int	g_sig_int;

char	*temp_hdoc(char *hdoc)
{
	int	fd;

	fd = open("temp_hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open: temp_hdoc"), NULL);
	write(fd, hdoc, ft_strlen(hdoc));
	close(fd);
	return ("temp_hdoc");
}

void	inp_cmd_run(t_table exp_table, char *in, char **hdoc, t_shell *shell)
{
	int				fd;
	int				in_fd;
	char			*inp;
	t_token_type	t_type;

	t_type = in_o_hdoc(shell->tokens, 0);
	if (t_type == D_LESS)
		inp = temp_hdoc(hdoc[0]);
	if (t_type == LESS)
		inp = in;
	fd = open(inp, 0);
	if (fd == -1)
	{
		perror("open: in_cmd_run");
		return ;
	}
	in_fd = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free_d_str(hdoc);
	ft_execve(exp_table.args[0], exp_table.args, shell);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	if (t_type == D_LESS)
		unlink(inp);
}

int	check_and_set(int *out_fd, char ***hdoc, t_shell *shell)
{
	*out_fd = dup(STDOUT_FILENO);
	if (*out_fd == -1)
		free_all(shell, "dup error", 127);
	if (expandor_hdoc(shell, 0) == false)
		return (close(*out_fd), 1);
	*hdoc = NULL;
	*hdoc = check_hdoc(shell->tables[0], shell);
	if (g_sig_int == 1)
	{
		close(*out_fd);
		free_all(shell, "no print", 3);
		free(*hdoc);
		g_sig_int = getpid();
		return (1);
	}
	if (expandor(shell, 0) == false)
		return (close(*out_fd), 1);
	if (shell->tables[0].args[0] == NULL)
		return (free_all(shell, "no print", 3), 1);
	return (0);
}

void	single_exec_run(t_shell *shell, t_single_exec_var *var)
{
	if (shell->tables[0].args[0] == NULL )
	{
		if (var->is_out == 0)
			close(var->out_fd);
		return (free_all(shell, "no print", 3));
	}
	if (is_builtin(shell->tables[0].args[0]) == 1)
	{
		if (var->is_out == 0)
			close(var->out_fd);
		free_d_str(var->hdoc);
		run_builtin(shell->tables[0], shell);
	}
	else if (shell->tables[0].args[1] != NULL || (shell->tables[0].in[0] \
	== NULL && shell->tables[0].heredoc[0] == NULL))
	{
		free_d_str(var->hdoc);
		if (var->is_out == 0)
			close(var->out_fd);
		ft_execve(shell->tables[0].args[0], shell->tables[0].args, shell);
	}
	else
		inp_cmd_run(shell->tables[0], var->in, var->hdoc, shell);
}

void	single_exec(t_shell *shell)
{
	t_single_exec_var	var;

	if (check_and_set(&(var.out_fd), &(var.hdoc), shell))
		return ;
	var.in = check_in(shell->tables[0]);
	var.is_out = output_check(shell->tables[0], 0, shell->tokens);
	if (var.is_out != 0 && shell->tables[0].args[0] == NULL)
	{
		dup2(var.out_fd, STDOUT_FILENO);
		close(var.out_fd);
		return (free_all(shell, "no print", 3));
	}
	if (var.is_out == -127)
		return (shell->exit_status = 1, free_all(shell, "no print", 3));
	single_exec_run(shell, &var);
	if (var.is_out != 0)
		dup2(var.out_fd, STDOUT_FILENO);
	close(var.out_fd);
}
