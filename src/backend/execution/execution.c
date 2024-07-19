/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:49 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 08:34:13 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_in(t_table table)
{
	int	i;

	if (table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (table.in[i] != NULL)
	{
		if (access(table.in[i], F_OK) == -1)
			return (NULL);
		i++;
	}
	return (table.in[i - 1]);
}

void	pipe_exec_init(t_pipe_exec_var *exec)
{
	exec->str_pid = NULL;
}

int	cat_or_echo(t_shell *shell)
{
	if (ft_strcmp(shell->tables->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(shell->tables->args[0], "cat") == 0)
		return (1);
	if (ft_strcmp(shell->tables->args[0], "wc") == 0)
		return (1);
	return (0);
}

void	last_command_init(t_shell *shell)
{
	char	*first_arg;
	int		c_or_e;

	c_or_e = 0;
	if (shell->tables->args[0] == NULL)
		return ;
	if (d_str_len(shell->tables->args) > 1)
		if (ft_strcmp(shell->tables->args[0], "echo") == 0 && \
			ft_strcmp(shell->tables->args[1], "$_") == 0)
			return ;
	if (d_str_len(shell->tables->args) > 1)
		c_or_e = cat_or_echo(shell);
	if (c_or_e == 0)
		first_arg = ft_strjoin("_=", shell->tables->args[0]);
	else
		first_arg = ft_strjoin("_=", shell->tables->args[1]);
	if (first_arg == NULL)
		(free(first_arg), free_all(shell, "malloc", 127));
	shell->env = add_env(shell->env, first_arg);
	if (shell->env == NULL)
		(free(first_arg), free_all(shell, "add_env", 127));
	free(first_arg);
}

void	execution(t_shell *shell)
{
	pipe_exec_init(&(shell->exec));
	shell->hdoc = NULL;
	if (shell->tables == NULL)
		return ;
	shell->table_len = shell->tables->table_len;
	if (shell->tables->table_len < 2)
	{
		last_command_init(shell);
		single_exec(shell);
	}
	else
		pipe_execution(shell, &(shell->exec));
}
