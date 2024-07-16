/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_inside_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:03:48 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/06 15:54:23 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_dollar(char *hdoc)
{
	int	i;

	i = 0;
	if (hdoc == NULL)
		return (NULL);
	while (hdoc[i] != '\0')
	{
		if (hdoc[i] == '$')
			return (hdoc);
		i++;
	}
	return (NULL);
}

char *get_last_non_exp_hdoc(t_table table, t_shell *shell)
{
	int		i;
	char	*non_exp_hdoc;

	i = 0;
	if (table.heredoc == NULL || table.heredoc[0] == NULL)
		return (NULL);
	while (table.heredoc[i] != NULL)
		i++;
	non_exp_hdoc = ft_strdup(table.heredoc[i - 1]);
	if (non_exp_hdoc == NULL)
		free_all(shell, "Malloc Error", 127);
	return (non_exp_hdoc);
}
int	quote_check(char *non_exp_hdoc)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	if (non_exp_hdoc == NULL)
		return (0);
	while (non_exp_hdoc[i] != '\0')
	{
		if (non_exp_hdoc[i] == '\'')
			quote++;
		if (non_exp_hdoc[i] == '"')
			quote++;
		i++;
	}
	if (quote > 0)
		return (1);
	return (0);
}

void	hdoc_in_question(t_shell *shell, char **hdoc, int *i)
{
	char	*exit_stat;
	char	*temp2;
	char	*temp3;

	exit_stat = ft_itoa(shell->exit_status);
	temp2 = (char *)malloc(*i + 1);
	if (temp2 == NULL)
		(free(exit_stat), free_all(shell, "Malloc Error", 127));
	temp2 = ft_strncpy(temp2, *hdoc, *i);
	temp2[*i] = '\0';
	temp3 = ft_strjoin(temp2, exit_stat);
	if (temp3 == NULL)
		(free(exit_stat), free(temp2), free_all(shell, "Malloc Error", 127));
	free(temp2);
	temp2 = temp3;
	temp3 = ft_strjoin(temp2, *hdoc + *i + 2);
	if (temp3 == NULL)
		(free(exit_stat), free(temp2), free_all(shell, "Malloc Error", 127));
	free(temp2);
	free(*hdoc);
	*hdoc = temp3;
	*i = *i + ft_strlen(exit_stat);
	free(exit_stat);
}

char	*get_dollar_name(t_shell *shell, char *hdoc, int *i)
{
	char	*dollar_name;
	int		j;

	dollar_name = NULL;
	j = *i + 1;
	while (hdoc[j] && is_alfa_num(hdoc[j]) == true)
	{
		dollar_name = ft_strjoin_char(dollar_name, hdoc[j]);
		if (dollar_name == NULL)
			(free(hdoc), free_all(shell, "Malloc Error\n", 127));
		j++;
	}
	dollar_name = ft_strjoin_char(dollar_name, '=');
	return (dollar_name);
}

char	*hdoc_inenv_loop(t_shell *shell, char *dollar)
{
	char	*expanded_dollar;
	int		i;

	i = 0;
	expanded_dollar = NULL;
	while(shell->env[i] && ft_strlen(dollar) > 1)
	{
		if (ft_strncmp(shell->env[i], dollar, ft_strlen(dollar)) == 0)
		{
			expanded_dollar = ft_strdup(shell->env[i] + ft_strlen(dollar));
			if (expanded_dollar == NULL)
				(free(dollar), free_all(shell, "Malloc Error\n", 127));
			return (expanded_dollar);
		}
		i++;	
	}
	return (expanded_dollar);
}

char	*hdoc_in_dollar(t_shell *shell, char *hdoc, int *i)
{
	char	*temp;
	char	*temp2;
	char	*dollar_name;
	char	*expanded_dollar;

	temp = (char *)malloc(*i + 1);
	if (temp == NULL)
		free_all(shell, "Malloc Error", 127);
	temp = ft_strncpy(temp, hdoc, *i);
	temp[*i] = '\0';
	dollar_name = get_dollar_name(shell, hdoc, i);
	expanded_dollar = hdoc_inenv_loop(shell, dollar_name);
	temp2 = ft_strjoin(temp, expanded_dollar);
	free(temp);
	if (temp2 == NULL)
		(free(expanded_dollar), free_all(shell, "Malloc Error", 127));
	temp = ft_strjoin(temp2, hdoc + *i + ft_strlen(dollar_name));
	free(temp2);
	free(dollar_name);
	if (temp == NULL)
		free_all(shell, "Malloc Error", 127);
	free(hdoc);
	*i = *i + ft_strlen(expanded_dollar) - 1;
	if (*i == -1)
		*i = 0;
	if (expanded_dollar != NULL)
		free(expanded_dollar);
	return (temp);
}

char	*in_expansion(t_shell *shell, char *hdoc)
{
	int	i;

	i = 0;
	while(hdoc[i] != '\0')
	{
		if (hdoc[i] == '$' && hdoc[i + 1] == '\0')
			break ;
		if (hdoc[i] == '$' && hdoc[i + 1] == ' ')
			i++;
		if (hdoc[i] == '$' && hdoc[i + 1] == '?')
			hdoc_in_question(shell, &hdoc, &i);
		if (hdoc[i] == '$')
			hdoc = hdoc_in_dollar(shell, hdoc, &i);
		if (hdoc[i] == '\0')
			break;
		i++;
	}
	
	return (hdoc);
}

char	*hdoc_in_expand(t_shell *shell, char *hdoc, char *non_exp_hdoc)
{
	if (is_dollar(hdoc) == NULL || quote_check(non_exp_hdoc) == 1)
	{
		if (non_exp_hdoc != NULL)
			free(non_exp_hdoc);
		return (hdoc);
	}
	if (non_exp_hdoc != NULL)
		free(non_exp_hdoc);
	hdoc = in_expansion(shell, hdoc);
	return (hdoc);
}
