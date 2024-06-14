/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/13 23:51:45 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_squo(char *content, int *i)
{
	(*i)++;
	// printf("content[i] = %s\n", content);
	while (content[*i] && content[*i] != '\'')
	{
		if (content[*i] == '\'')
			return ;
		(*i)++;
	}
	return ;
}

static void	check_dquo(char *content, int *i)
{
	(*i)++;
	while (content[*i] && content[*i] != '"')
	{
		if (content[*i] == '"')
			return ;
		(*i)++;
	}
	return ;
}

bool	content_check(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			check_squo(content, &i);
			if (!content[i])
				return (false);
		}
		else if (content[i] == '"')
		{
			check_dquo(content, &i);
			if (!content[i])
				return (false);
		}
		i++;
	}
	return (true);
}

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

//added the get_update_cmd after expansion.

bool	expandor(t_shell *shell, int table_num)
{
	if (arg_expand(&(shell->tables[table_num].args), shell) == false
		|| redir_expand(shell->tables[table_num].in, shell) == false
		|| redir_expand(shell->tables[table_num].out, shell) == false
		|| redir_expand(shell->tables[table_num].append, shell) == false
		|| hdoc_expand(shell->tables[table_num].heredoc, shell) == false
		|| check_in_expandor(shell->tables[table_num], shell) == false ) 
	{
		if (shell->table_len == 1 || shell->table_len == table_num + 1)
			free_all(shell, "no print", 3);
		return (false);
	}

	return (true);
}