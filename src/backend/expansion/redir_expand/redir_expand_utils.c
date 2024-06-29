/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:48 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/27 22:56:14 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**word_split(char *new_exp)
{
	char	**new_d_exp;

	new_d_exp = ft_split(new_exp, ' ');
	if (new_d_exp == NULL)
		return (NULL);
	return (new_d_exp);
}

char	**one_dollar(char **new_content, t_shell *shell, int *i)
{
	char	**question_mark;

	question_mark = (char **)malloc(sizeof(char *) * 2);
	if (question_mark == NULL)
	{
		free_d_str(new_content);
		free_all(shell, "Malloc Error\n", 127);
	}
	question_mark[0] = ft_strdup("$");
	if (question_mark[0] == NULL)
	{
		free(question_mark);
		free_d_str(new_content);
		free_all(shell, "Malloc Error\n", 127);
	}
	question_mark[1] = NULL;
	new_content = add_new_content(new_content, question_mark, shell);
	(*i)++;
	return (new_content);
}
