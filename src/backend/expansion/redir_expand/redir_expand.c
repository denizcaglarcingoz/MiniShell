/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:48 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/12 20:25:45 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**word_split(char *new_exp, t_shell *shell)
{
	char	**new_d_exp;

	new_d_exp = ft_split(new_exp, ' ');
	if (new_d_exp == 0)
		free_all(shell, "Malloc Error\n", 127);
	return (new_d_exp);
}

void	exps_loop(char **to_exp, char ***new_d_exp, char **new_exp, \
t_shell *shell)
{
	char	*temp;
	int		i;

	i = 0;
	while (shell->env[i] && ft_strlen(*to_exp) > 1)
	{
		if (ft_strncmp(*to_exp, shell->env[i], ft_strlen(*to_exp)) == 0)
		{
			temp = *new_exp;
			*new_exp = ft_strjoin(*new_exp, shell->env[i] + ft_strlen(*to_exp));
			free(temp);
			if (*new_exp == NULL)
			{
				free_d_str(*new_d_exp);
				free_all(shell, "Malloc Error\n", 127);
			}
			*new_d_exp = word_split(*new_exp, shell);
			break ;
		}
		i++;
	}
	free(*to_exp);
}

char	**exps(char *to_exp, t_shell *shell)
{
	char	**new_d_exp;
	char	*new_exp;

	if (to_exp == NULL || to_exp[0] == '\0')
		return (NULL);
	to_exp = ft_strjoin_char(to_exp, '=');
	if (to_exp == NULL)
		free_all(shell, "Malloc Error\n", 127);
	new_exp = NULL;
	new_d_exp = NULL;
	exps_loop(&to_exp, &new_d_exp, &new_exp, shell);
	if (new_exp != NULL)
		free(new_exp);
	return (new_d_exp);
}

char **one_dollar(char **new_content, t_shell *shell, int *i)
{
	char **question_mark;

	question_mark = (char **)malloc(sizeof(char *) * 2);
	question_mark[0] = ft_strdup("$");
	if (question_mark[0] == NULL)
	{
		free_d_str(new_content);
		free_all(shell, "Malloc Error\n", 127);
	}
	new_content = add_new_content(new_content, question_mark, shell);
	(*i)++;
	return (new_content);
}

char	**exp_dollar(char *content, int *i, char **new_content, t_shell *shell)
{
	char	*to_exp;
	char	**d_exp;

	to_exp = NULL;
	if (content[*i] == '$' && content[*i + 1] == '\0')
		return (one_dollar(new_content, shell, i));
	(*i)++;
	if (content[*i] == '?')
	{
		(*i)++;
		d_exp = dollar_question(shell);
		new_content = add_new_content(new_content, d_exp, shell);
		return (new_content);
	}
	while (content[*i] && is_alfa_num(content[*i]) == true)
	{
		to_exp = ft_strjoin_char(to_exp, content[*i]);
		if (to_exp == NULL)
			to_exp_fail(new_content, content, shell);
		(*i)++;
	}
	d_exp = exps(to_exp, shell);
	new_content = add_new_content(new_content, d_exp, shell);
	return (new_content);
}

bool	redir_expand(char **content, t_shell *shell)
{
	int		i;
	char	**exp;

	i = 0;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
		if (str_is_alfa_num(content[i]) == false)
		{
			exp = exp_check(content[i], shell);
			if (exp[1] != 0 || (exp[0][0] == '\0' && exp[1] == NULL))
			{
				printf("bash: %s: ambiguous redirect\n", content[i]);
				return (false);
			}
			content[i] = exp[0];
		}
		i++;
	}
	return (true);
}
