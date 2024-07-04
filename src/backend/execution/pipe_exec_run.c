/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:00:10 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 21:11:44 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_inp_fd(t_token_type *t_type, char **inp, char *in, t_shell *shell)
{
	int fd;

	if (*t_type == D_LESS)
		*inp = temp_hdoc(shell->hdoc[shell->exec.i]);
	if (*t_type == LESS)
		*inp = in;
	if (*inp == NULL)
		return (-1);
	fd = open(*inp, 0);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

void wait_ft(t_token_type t_type, char *inp)
{
	wait(NULL);
	if (t_type == D_LESS)
		unlink(inp);
	exit(0);
}

void pipe_inp_cmd_run(t_table exp_table, char *in, t_shell *shell)
{
	int fd;
	char *inp;
	t_token_type t_type;

	inp = NULL;

	t_type = in_o_hdoc(shell->tokens, shell->table_id);
	fd = init_inp_fd(&t_type, &inp, in, shell);
	if (fd == -1)
		return;
	dup2(fd, STDIN_FILENO);
	close(fd);
	free_d_str_till(shell->hdoc, shell->table_len - 1);
	ft_pipe_execve(exp_table.args[0], exp_table.args, shell);
}

void not_in_file_p(char **in, t_shell *shell)
{
	int i;

	i = 0;

	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break;
		i++;
	}
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 127);
}

void not_in_file(char **in, t_shell *shell)
{
	int i;

	i = 0;

	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break;
		i++;
	}
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 0);
}

void pipe_exec_run(t_table table, int table_id, t_shell *shell)
{
	char *in;

	in = check_in(table);
	if (table.in[0] != NULL && in == NULL)
		not_in_file_p(table.in, shell);
	output_check(table, table_id, shell->tokens);
	shell->table_id = table_id;
	if (is_builtin(table.args[0]) == 1)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		run_builtin(table, shell);
		free_all_env(shell->env);
		free_all_env(shell->exported);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(shell->exit_status);
	}
	else if ((table.args[1] != NULL || table.heredoc[0] == NULL) && table.in[0] == NULL)
	{
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		ft_pipe_execve(table.args[0], table.args, shell);
	}
	else
		pipe_inp_cmd_run(table, in, shell);
}
