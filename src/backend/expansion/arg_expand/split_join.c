/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:30 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 02:43:17 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_dup(char **joined, int *join, char **dup, int dup_int)
{
	while (dup[dup_int] != NULL)
	{
		if (dup[dup_int][0] == '\0')
		{
			if (dup[dup_int][1] == '\0' && dup[dup_int][2] == '\0')
				joined[*join] = empty_txt_nothing();
			if (dup[dup_int][1] == '"')
				joined[*join] = empty_d_quo_txt();
			else if (dup[dup_int][1] == '$')
				joined[*join] = empty_dollar_txt_s();
		}
		else
			joined[*join] = ft_strdup(dup[dup_int]);
		(*join)++;
		dup_int++;
	}
	return (joined);
}

int	empty_assign(char **content, char **exp, int *k, char **joined)
{
	if (content[*k][1] == '"')
	{
		joined[*k] = empty_d_quo_txt();
		if (joined[*k] == NULL)
		{
			free_d_str(exp);
			free_d_str_till(joined, *k - 1);
			return (1);
		}
	}
	else if (content[*k][1] == '$')
	{
		joined[*k] = empty_dollar_txt_s();
		if (joined[*k] == NULL)
		{
			free_d_str(exp);
			free_d_str_till(joined, *k - 1);
			return (1);
		}
	}
	return (0);
}

char	**join_init(char **content, char **exp, int add_split_from, \
char **joined)
{
	int		k;

	k = 0;
	while (k < add_split_from && content[k] != NULL)
	{
		if (content[k][0] == '\0')
		{
			if (empty_assign(content, exp, &k, joined))
				return (NULL);
		}
		else
		{
			joined[k] = ft_strdup(content[k]);
			if (joined[k] == NULL)
				return (free_d_str(exp), free_d_str_till(joined, k - 1), NULL);
		}
		k++;
	}
	join_dup(joined, &k, exp, 0);
	join_dup(joined, &k, content, ++add_split_from);
	joined[k] = NULL;
	return (joined);
}

char	**join_malloc(char **exp, t_shell *shell, int join_len)
{
	char	**joined;

	joined = (char **)malloc(sizeof(char *) * (join_len + 1));
	if (joined == NULL)
	{
		free_d_str(exp);
		free_all(shell, "Malloc Error\n", 127);
	}
	return (joined);
}

char	**split_join(char **content, char **exp, int add_split_from, \
t_shell *shell)
{
	char	**joined;
	int		content_len;
	int		exp_len;

	if (exp == NULL)
		return (content);
	if (content && content[0][0] == '\0' && content[1] == NULL)
		return (exp);
	content_len = d_str_len(content) - 1;
	exp_len = d_str_len(exp);
	joined = join_malloc(exp, shell, content_len + exp_len);
	joined = join_init(content, exp, add_split_from, joined);
	if (joined == NULL)
		free_all(shell, "Malloc Error\n", 127);
	free_d_str(content);
	return (joined);
}
