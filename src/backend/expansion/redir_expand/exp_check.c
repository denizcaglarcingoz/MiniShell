/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:43 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 16:37:05 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_content_dquo(char ***new_content, char **content, \
int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*i)++;
	(*new_content)[j - 1] = exp_d_quo(*content, i, \
	(*new_content)[j - 1], shell);
	if ((*new_content)[j - 1] == NULL)
	{
		free_d_str(*new_content);
		free_all(shell, "new_content[j - 1]", 127);
	}
}

void	new_content_squo(char ***new_content, \
char **content, int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*i)++;
	(*new_content)[j - 1] = exp_s_quo(*content, i, (*new_content)[j - 1]);
	if ((*new_content)[j - 1] == NULL)
	{
		free_d_str(*new_content);
		free_all(shell, "new_content[j - 1]", 127);
	}
}

void	new_content_alt(char ***new_content, \
char **content, int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = ft_strjoin_char((*new_content)[j - 1], \
	(*content)[*i]);
	if ((*new_content)[j - 1] == NULL)
	{
		free_d_str(*new_content);
		free_all(shell, "new_content[j - 1]", 127);
	}
	(*i)++;
}

void	init_new_content(char ***new_content, t_shell *shell)
{
	*new_content = (char **)malloc(sizeof(char *) * 2);
	if (!(*new_content))
		free_all(shell, "new_content malloc", 127);
	(*new_content)[0] = ft_strdup("");
	if (!((*new_content)[0]))
	{
		free(*new_content);
		free_all(shell, "new_content[0]", 127);
	}
	(*new_content)[1] = NULL;
}

char	**exp_check(char *content, t_shell *shell)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = NULL;
	if (content == NULL)
		return (NULL);
	init_new_content(&new_content, shell);
	while (content[i])
	{
		if (content[i] == '$')
			new_content = exp_dollar(content, &i, new_content, shell);
		else if (content[i] == '"')
			new_content_dquo(&new_content, &content, &i, shell);
		else if (content[i] == '\'')
			new_content_squo(&new_content, &content, &i, shell);
		if (content[i] != '\0' && content[i] != '$' && content[i] \
		!= '"' && content[i] != '\'')
			new_content_alt(&new_content, &content, &i, shell);
		if (!content[i])
			break ;
	}
	return (new_content);
}
