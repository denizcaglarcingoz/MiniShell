/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/11 22:25:12 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_squo(char *content, int *i)
{
	(*i)++;
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

bool	check_in_expandor(t_table exp_table)
{
	int	i;

	i = 0;
	while (exp_table.in[i] != NULL)
	{
		if (access(exp_table.in[i], F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);//----------------------------
			ft_putstr_fd(exp_table.in[i], 2);
			ft_putstr_fd("No such file or directory\n", 2);//--------------------
			//printf("bash: %s: syntax error: no such file\n", exp_table.in[i]);
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
		|| check_in_expandor(shell->tables[table_num]) == false)
	{
		free_all(shell, "no print", 0);
		return (false);
	}

	return (true);
}
