/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:04 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 21:39:09 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_out_check(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	int	out_check;

	out_check = -1;
	if (prev_read_fd != -1)
		(dup2(prev_read_fd, STDIN_FILENO), close(prev_read_fd));
	if (i + 1 < shell->tables->table_len)
	{
		if (shell->tables[i].args[0] != NULL || shell->tables[i].out[0] != NULL)
		{
			out_check = output_check(shell->tables[i], i, shell->tokens);
			if (out_check == -1)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			else if (out_check == -127)
				(close(pipefd[1]), free_all(shell, "no print", 127));
		}
	}
	if (i + 1 == shell->tables->table_len)
	{
		if (shell->tables[i].args[0] == NULL || shell->tables[i].out[0] != NULL)
		{
			out_check = output_check(shell->tables[i], i, shell->tokens);
			if (out_check == -127)
				(close(pipefd[1]), free_all(shell, "no print", 127));
		}
	}
}

void	child_pro(t_shell *shell, int pipefd[2], int prev_read_fd, int i)
{
	close(pipefd[0]);
	child_out_check(shell, pipefd, prev_read_fd, i);
	close(pipefd[1]);
	if ((shell->tables[i]).args[0] == NULL)
	{	
		free_d_str_till(shell->hdoc, shell->table_len - 1);
		free_all(shell, "", 0);
		exit(0);
	}
	else
		pipe_exec_run(shell->tables[i], i, shell);
}

void	expansion_ok_run(t_shell *shell, t_pipe_exec_var *exec)
{
	exec->pid = pipe_fork(shell, exec->pipefd);
	if (exec->pid == 0)
	{
		free(exec->str_pid);
		close(exec->std_in);
		close(exec->std_out);
		child_pro(shell, exec->pipefd, exec->prev_read_fd, exec->i);
	}
	else
	{
		close(exec->pipefd[1]);
		if (exec->prev_read_fd != -1)
			close(exec->prev_read_fd);
		exec->prev_read_fd = exec->pipefd[0];
	}
}

void	pipe_closing_args(t_shell *shell, t_pipe_exec_var *exec)
{
	int		status;
	pid_t	result;

	status = 0;
	if (g_sig_int == SIGUSR1)
		free_d_str(shell->hdoc);
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_int_exec);
	if (exec->expandor_check == 0)
	{
		get_exit_code_p(shell, exec);
		free_all(shell, "no exit", 3);
	}
	if (exec->expandor_check == 0 && exec->pipefd[0] != -1)
		close(exec->pipefd[0]);
	if (exec->pid != -1)
		result = waitpid(exec->pid, &status, WNOHANG);
	if (exec->pid != -1 && result == 0)
		waitpid(exec->pid, &status, 0);
	free_d_str_till(shell->hdoc, shell->table_len - 1);
	dup2(exec->std_in, STDIN_FILENO);
	close(exec->std_in);
	dup2(exec->std_out, STDOUT_FILENO);
	close(exec->std_out);
	free(exec->str_pid);
	signal(SIGINT, sigint_handler_sigint);
	kill(0, SIGINT);
	signal(SIGINT, sigint_handler_int);
	signal(SIGQUIT, SIG_IGN);
}

int is_hdoc_exist(t_shell *shell)
{
	int	i;
	int k;
	
	k = 0;
	i = 0;
	while (i < shell->table_len)
	{
		if (shell->tables[i].heredoc[0] != NULL)
			k++;
		i++;
	}
	if (k == 0)
		return (0);
	return (1);
}

int	pipe_hdocs(t_shell *shell)
{
	int	i;
	
	if (is_hdoc_exist(shell) == 0)
		return (0);
	shell->hdoc = (char **)malloc(sizeof(char *) * (shell->table_len + 1));
	if (shell->hdoc == NULL)
		free_all(shell, "malloc fail", 127);
	shell->hdoc[shell->table_len] = NULL;
	i = 0;
	while (i < shell->table_len)
	{
		if (expandor_hdoc(shell, i) == false)
			return  (1);
		if (shell->tables[i].heredoc[0] == NULL)
			shell->hdoc[i] = ft_strdup("");
		else
			shell->hdoc[i] = check_hdoc_p(shell->tables[i], shell);
		if (g_sig_int == SIGUSR1)
			return (free_all(shell, "", 0), 1);
		i++;
	}
	return (0);
}

void	pipe_execution(t_shell *shell, t_pipe_exec_var *exec)
{
	exec_init(exec, shell);
	if (pipe_hdocs(shell) == 1)
	{	
		signal(SIGINT, sigint_handler_sigint);
		kill(0, SIGINT);
		signal(SIGINT, sigint_handler_int);
		return ;
	}
	while (exec->i < shell->table_len)
	{
		if (expandor(shell, exec->i) == false)
			exec->expandor_check = 1;
		if (exec->expandor_check == 0)
			expansion_ok_run(shell, exec);
		exec->str_pid[exec->i] = exec->pid;
		(exec->i)++;
		if (exec->i < shell->table_len)
			exec->expandor_check = 0;
	}
	pipe_closing_args(shell, exec);
}
