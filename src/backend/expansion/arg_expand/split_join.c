/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:30 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:29:31 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_malloc(char **content, char **exp, t_shell *shell, int join_len)
{
	char	**joined;

	joined = (char **)malloc(sizeof(char *) * (join_len + 1));
	if (joined == NULL)
	{
		free_d_str(content);
		free_d_str(exp);
		free_all(shell, "Malloc Error\n", 127);
	}
	return (joined);
}

char	**join_dup(char **joined, int *join, char **dup, int dup_int)
{
	while (dup[dup_int] != NULL)
	{
		joined[*join] = ft_strdup(dup[dup_int]);
		(*join)++;
		dup_int++;
	}
	return (joined);
}

char	**join_init(char **content, char **exp, int add_split_from, \
char **joined)
{
	int		i;
	int		k;

	k = 0;
	while (k < add_split_from && content[k] != NULL)
	{
		joined[k] = ft_strdup(content[k]);
		k++;
	}
	i = 0;
	join_dup(joined, &k, exp, i);
	join_dup(joined, &k, content, ++add_split_from);
	joined[k] = NULL;
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
	joined = join_malloc(content, exp, shell, content_len + exp_len);
	joined = join_init(content, exp, add_split_from, joined);
	free_d_str(content);
	return (joined);
}
