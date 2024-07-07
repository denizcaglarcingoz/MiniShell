/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:21 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/07 21:29:32 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	len_loop(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) == 0)
			(*k)++;
		i++;
	}
}

void	len_loop_2(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i][0] == '\0')
		{
			if (content[i][1] == '"')
				(*k)++;
		}
		else
			(*k)++;
		i++;
	}
}

void	free_content(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
	content = NULL;
}

void	empt_str_dup(char **content, char ***new_content, \
int *k, t_shell *shell)
{
	(*new_content)[*k] = ft_strdup("");
	if ((*new_content)[*k] == NULL)
	{
		free_d_str(content);
		free_d_str_till(*new_content, *k - 1);
		free_all(shell, "New C Malloc Error", 127);
	}
	(*k)++;
}

void	n_content_dup(char *content, char ***new_content, \
int *k, t_shell *shell)
{
	(*new_content)[*k] = ft_strdup(content);
	if ((*new_content)[*k] == NULL)
	{
		free(content);
		free_d_str_till(*new_content, *k - 1);
		free_all(shell, "New C Malloc Error", 127);
	}
	(*k)++;
}
