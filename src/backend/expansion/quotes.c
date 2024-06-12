/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/11 15:50:30 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quo_exp(char *exp, t_shell *shell)
{
	char	*new_exp;
	int		i;

	i = 0;
	exp = ft_strjoin_char(exp, '=');
	new_exp = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(exp, shell->env[i], ft_strlen(exp)) == 0)
		{
			new_exp = ft_strjoin(new_exp, shell->env[i] + ft_strlen(exp));
		}
		i++;
	}
	free(exp);
	return (new_exp);
}

char	*quo_exp_dollar(char *cntnt, int *i, char *new_cntnt, \
t_shell *shell)
{
	char	*exp;
	char	*temp;

	temp = new_cntnt;
	(*i)++;
	if (cntnt[*i] == '?')
	{
		(*i)++;
		exp = quo_dollar_question(shell);
		new_cntnt = ft_strjoin(new_cntnt, exp);
		free(temp);
		free(exp);
		if (new_cntnt == NULL)
			free_all(shell, "Malloc Error\n", 127);
		return (new_cntnt);
	}
	exp = ft_strdup("");
	while (cntnt[*i] && is_alfa_num(cntnt[*i]) == true)
	{
		exp = ft_strjoin_char(exp, cntnt[*i]);
		(*i)++;
	}
	exp = quo_exp(exp, shell);
	new_cntnt = ft_strjoin(new_cntnt, exp);
	free(temp);
	free(exp);
	if (new_cntnt == NULL)
		free_all(shell, "Malloc Error\n", 127);
	return (new_cntnt);
}

char	*exp_d_quo(char *cntnt, int *i, char *new_cntnt, t_shell *shell)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '"')
	{
		if (cntnt[*i] == '$' && cntnt[*i + 1] != ' ' && cntnt[*i + 1] != '"')
			new_cntnt = quo_exp_dollar(cntnt, i, new_cntnt, shell);
		if (!cntnt[*i] || cntnt[*i] == '"')
			break ;
		if (cntnt[*i] != '$'|| (cntnt[*i] == '$' && cntnt[*i + 1] == ' ') || (cntnt[*i] == '$' && cntnt[*i + 1] == '"'))
		{
			new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
			if (new_cntnt == NULL)
				return (NULL);
			(*i)++;
		}
	}
	if (cntnt[*i] && cntnt[*i] == '"')
		(*i)++;
	return (new_cntnt);
}

char	*exp_s_quo(char *cntnt, int *i, char *new_cntnt)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '\'')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			return (NULL);
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '\'')
		(*i)++;
	return (new_cntnt);
}
