/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand_quo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:08 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 20:19:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hdoc_exp_d_quo(char *cntnt, int *i, char *new_cntnt, t_shell *shell)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '"')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			free_all(shell, "new_cntnt malloc", 127);
		if (!cntnt[*i] || cntnt[*i] == '"')
			break ;
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '"')
		(*i)++;
	return (new_cntnt);
}

char	*hdoc_exp_s_quo(char *cntnt, int *i, char *new_cntnt, t_shell *shell)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '\'')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			free_all(shell, "new_cntnt malloc", 127);
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '\'')
		(*i)++;
	return (new_cntnt);
}

void	hdoc_new_content_dquo(char ***new_content, char **content, \
int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = hdoc_exp_d_quo(*content, i, \
	(*new_content)[j - 1], shell);
}

void	hdoc_new_content_squo(char ***new_content, \
char **content, int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = \
	hdoc_exp_s_quo(*content, i, (*new_content)[j - 1], shell);
}
