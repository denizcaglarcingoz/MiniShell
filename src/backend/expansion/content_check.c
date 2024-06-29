/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:51 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 20:25:18 by dcingoz          ###   ########.fr       */
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
