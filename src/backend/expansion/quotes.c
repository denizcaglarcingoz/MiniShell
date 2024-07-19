/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 15:29:32 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quo_exp(char *exp, t_shell *shell)
{
	char	*new_exp;
	char	*temp;
	int		i;

	i = 0;
	exp = ft_strjoin_char(exp, '=');
	if (exp == NULL)
		return (NULL);
	new_exp = ft_strdup("");
	if (new_exp == NULL)
		return (NULL);
	temp = new_exp;
	while (shell->env[i])
	{
		if (ft_strncmp(exp, shell->env[i], ft_strlen(exp)) == 0)
		{
			new_exp = ft_strjoin(new_exp, shell->env[i] + ft_strlen(exp));
			if (new_exp == NULL)
				return (NULL);
			free(temp);
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
		return (quo_dollar_question(i, new_cntnt, shell));
	exp = ft_strdup("");
	if (exp == NULL)
		return (NULL);
	while (cntnt[*i] && is_alfa_num(cntnt[*i]) == true)
	{
		exp = ft_strjoin_char(exp, cntnt[*i]);
		if (exp == NULL)
			return (NULL);
		(*i)++;
	}
	exp = quo_exp(exp, shell);
	if (exp == NULL)
		return (NULL);
	new_cntnt = ft_strjoin(new_cntnt, exp);
	free(exp);
	if (new_cntnt == NULL)
		return (NULL);
	return (free(temp), new_cntnt);
}

int	exp_d_quo_join_char_if_check(char *cntnt, int *i)
{
	if (cntnt[*i] != '$' || \
		(cntnt[*i] == '$' && (cntnt[*i + 1] == '/' \
		|| cntnt[*i + 1] == ' ')) || \
		(cntnt[*i] == '$' && cntnt[*i + 1] == '"'))
	{
		return (1);
	}
	return (0);
}

char	*exp_d_quo(char *cntnt, int *i, char *new_cntnt, t_shell *shell)
{
	while (cntnt[*i] && cntnt[*i] != '"')
	{
		if (cntnt[*i] == '$' && cntnt[*i + 1] != ' ' \
			&& cntnt[*i + 1] != '/' && cntnt[*i + 1] != '"')
		{
			new_cntnt = quo_exp_dollar(cntnt, i, new_cntnt, shell);
			if (new_cntnt == NULL)
				return (NULL);
		}
		if (!cntnt[*i] || cntnt[*i] == '"')
			break ;
		if (exp_d_quo_join_char_if_check(cntnt, i) == 1)
		{
			new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
			if (new_cntnt == NULL)
				return (NULL);
			(*i)++;
		}
	}
	if (cntnt[*i] && cntnt[*i] == '"')
		(*i)++;
	if (ft_strlen(new_cntnt) == 0 && new_cntnt[0] == '\0')
		(free(new_cntnt), new_cntnt = empty_d_quo_txt());
	return (new_cntnt);
}

char	*exp_s_quo(char *cntnt, int *i, char *new_cntnt)
{
	while (cntnt[*i] && cntnt[*i] != '\'')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			return (NULL);
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '\'')
		(*i)++;
	if (ft_strlen(new_cntnt) == 0 && new_cntnt[0] == '\0')
	{
		free(new_cntnt);
		new_cntnt = empty_s_quo_txt();
		if (new_cntnt == NULL)
			return (NULL);
	}
	return (new_cntnt);
}
