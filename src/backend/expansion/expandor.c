/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 02:52:36 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_such_file(char *in, t_shell *shell)
{
	ft_putstr_fd("minishell: line 1: ", 2);
	ft_putstr_fd(in, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	shell->exit_status = 1;
}

bool	check_in_expandor(t_table exp_table, t_shell *shell)
{
	int	i;

	i = 0;
	while (exp_table.in[i] != NULL)
	{
		if (access(exp_table.in[i], F_OK) == -1)
		{
			no_such_file(exp_table.in[i], shell);
			return (false);
		}
		i++;
	}
	return (true);
}
// || check_in_expandor(shell->tables[table_num], shell) == false

bool	expandor(t_shell *shell, int table_num)
{
	shell->exp_space_flag_end = 0;
	shell->exp_space_flag_start = 0;
	if (redir_expand(shell->tables[table_num].in, shell) == false
		|| arg_expand(&(shell->tables[table_num].args), shell) == false
		|| redir_expand(shell->tables[table_num].out, shell) == false
		|| redir_expand(shell->tables[table_num].append, shell) == false)
	{
		if (shell->tables->table_len == 1
			|| shell->tables->table_len == table_num + 1)
			free_all(shell, "no print", 3);
		return (false);
	}
	return (true);
}

bool	expandor_hdoc(t_shell *shell, int table_num)
{
	if (hdoc_expand(shell->tables[table_num].heredoc, shell) == false)
	{
		free_all(shell, "no print", 3);
		return (false);
	}
	return (true);
}
