/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:08 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 09:58:56 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdoc_new_content_alt(char ***new_content, \
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

void	hdoc_init_new_content(char ***new_content, t_shell *shell)
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

char	**hdoc_exp_check(char *content, t_shell *shell)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = NULL;
	if (content == NULL)
		return (NULL);
	if (ft_strlen(content) == 2 && content[0] == '"' && content[1] == '"')
		return (NULL);
	hdoc_init_new_content(&new_content, shell);
	while (content[i])
	{
		if (content[i] == '"')
			hdoc_new_content_dquo(&new_content, &content, &i, shell);
		else if (content[i] == '\'')
			hdoc_new_content_squo(&new_content, &content, &i, shell);
		if (content[i] != '\0' && content[i] \
		!= '"' && content[i] != '\'')
			hdoc_new_content_alt(&new_content, &content, &i, shell);
		if (!content[i])
			break ;
	}
	return (new_content);
}

bool	hdoc_expand(char **content, t_shell *shell)
{
	int		i;
	char	**exp;

	i = 0;
	while (content[i])
	{
		if (content_check(content[i]) == false)
			return (printf("minishell: syntax error\n"), false);
		if (str_is_alfa_num(content[i]) == false)
		{
			exp = hdoc_exp_check(content[i], shell);
			if (exp == NULL || exp[1] != 0 || (exp[0][0] == '\0' \
				&& exp[1] == NULL))
				return (ft_putstr_fd("bash: ambiguous redirect\n", 2), false);
			free(content[i]);
			content[i] = ft_strdup(exp[0]);
			free_d_str(exp);
			if (content[i] == NULL)
				free_all(shell, "content malloc", 127);
		}
		i++;
	}
	return (true);
}
