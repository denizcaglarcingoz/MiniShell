/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:48 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 10:03:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_space_flag(char *new_exp, t_shell *shell)
{
	int	i;

	i = 0;
	if (new_exp == NULL || new_exp[0] == '\0')
		return ;
	shell->exp_space_flag_start = 0;
	shell->exp_space_flag_end = 0;
	if (new_exp[0] == ' ')
		shell->exp_space_flag_start = 1;
	while (new_exp[i])
		i++;
	i--;
	if (new_exp[i] == ' ')
		shell->exp_space_flag_end = 1;
}

int	env_loop(char **to_exp, char ***new_d_exp, char **new_exp, \
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
				return (free_d_str(*new_d_exp), free(to_exp), 1);
			exp_space_flag(*new_exp, shell);
			*new_d_exp = word_split(*new_exp);
			if (*new_d_exp == NULL)
				return (free(*new_exp), free(to_exp), 1);
			break ;
		}
		i++;
	}
	free(*to_exp);
	return (0);
}

char	**exps(char *to_exp, t_shell *shell, char **new_content)
{
	char	**new_d_exp;
	char	*new_exp;

	if (to_exp == NULL || to_exp[0] == '\0')
		return (NULL);
	to_exp = ft_strjoin_char(to_exp, '=');
	if (to_exp == NULL)
		(free_d_str(new_content), free_all(shell, "Malloc Error\n", 127));
	new_exp = NULL;
	new_d_exp = NULL;
	if (env_loop(&to_exp, &new_d_exp, &new_exp, shell) == 1)
		(free_d_str(new_content), free_all(shell, "Malloc Error\n", 127));
	if (new_exp != NULL)
		free(new_exp);
	return (new_d_exp);
}

char	**exp_dollar(char *content, int *i, char **new_content, t_shell *shell)
{
	char	*to_exp;
	char	**d_exp;

	to_exp = NULL;
	if (content[*i] == '$' && (content[*i + 1] == '\0' \
		|| content[*i + 1] == '/'))
		return (one_dollar(new_content, shell, i));
	(*i)++;
	if (content[*i] == '?')
	{
		(*i)++;
		d_exp = dollar_question(shell);
		return (add_new_content(new_content, d_exp, shell));
	}
	while (content[*i] && is_alfa_num(content[*i]) == true)
	{
		to_exp = ft_strjoin_char(to_exp, content[*i]);
		if (to_exp == NULL && free_d_str_int(new_content) == 1)
			free_all(shell, "Malloc Error\n", 127);
		(*i)++;
	}
	d_exp = exps(to_exp, shell, new_content);
	if (d_exp == NULL)
		d_exp = empty_dollar_txt_d();
	return (add_new_content(new_content, d_exp, shell));
}

bool	redir_expand(char **content, t_shell *shell)
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
			exp = exp_check(content[i], shell);
			if (exp[0] == NULL || exp[1] != 0 || \
				(exp[0][0] == '\0' && exp[1] == NULL))
				return (ambigous_return(exp, shell, content, i));
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
