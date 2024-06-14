/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:30 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 23:54:23 by dcingoz          ###   ########.fr       */
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
		if (dup[dup_int][0] == '\0')
		{
			if (dup[dup_int][1] == '"')
			{	
				// write(1, "empty_d_quo_txt\n", 16);
				joined[*join] = empty_d_quo_txt();
			}
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

char	**join_init(char **content, char **exp, int add_split_from, \
char **joined)
{
	int		i;
	int		k;

	k = 0;
	while (k < add_split_from && content[k] != NULL)
	{
		if (content[k][0] == '\0')
		{
			if (content[k][1] == '"')
			{	
				joined[k] = empty_d_quo_txt();
			}
			else if (content[k][1] == '$')
				joined[k] = empty_dollar_txt_s();
		}
		else
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
	// printf("joined_len: %d\n", exp_len + content_len);
	joined = join_malloc(content, exp, shell, content_len + exp_len);
	joined = join_init(content, exp, add_split_from, joined);
	free_d_str(content);
	// print_d_str(joined);
	
	// if (joined[0][0] == '\0')
	// {
	// 	write(1, "joined", 6);
	// 	write(1, &(joined[0][0]), 1);
	// 	write(1, "1\n", 2);
	// 	if (joined[0][1] != '\0')
	// 	{
	// 		write(1, "joined", 6);
	// 		write(1, &(joined[0][1]), 1);
	// 		write(1, "2\n", 2);
	// 		if (joined[0][2] == '\0')
	// 		{
	// 			write(1, "joined", 6);
	// 			write(1, &(joined[0][2]), 1);
	// 			write(1, "3\n", 2);
	// 		}
	// 	}
	// }
	return (joined);
}
