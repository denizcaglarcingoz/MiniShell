/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_inside_exp_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:16:18 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/16 20:25:28 by dcingoz          ###   ########.fr       */
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

char	*get_last_non_exp_hdoc(t_table table, t_shell *shell)
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

char	*temp_init(t_shell *shell, char *hdoc, int *i)
{
	char	*temp;

	temp = (char *)malloc(*i + 1);
	if (temp == NULL)
		free_all(shell, "Malloc Error", 127);
	temp = ft_strncpy(temp, hdoc, *i);
	temp[*i] = '\0';
	return (temp);
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
