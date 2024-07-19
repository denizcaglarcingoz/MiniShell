/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:27 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 02:43:06 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**n_content_alloc_fill(char **content, int k, t_shell *shell)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = (char **)malloc(sizeof(char *) * (k + 1));
	if (new_content == NULL)
		(free_d_str(content), free_all(shell, "New C Malloc Error", 127));
	new_content[k] = NULL;
	k = 0;
	while (content[i])
	{
		if (content[i][0] == '\0')
		{
			if (content[i][1] == '"')
				empt_str_dup(content, &new_content, &k, shell);
		}
		else
			n_content_dup(content[i], &new_content, &k, shell);
		i++;
	}
	return (new_content);
}

int	check_expand_content(char ***content, int *i, t_shell *shell)
{
	int		exp_len;
	char	**exp;

	exp = exp_check((*content)[*i], shell);
	*content = split_join((*content), exp, *i, shell);
	exp_len = 0;
	while (exp[exp_len] != NULL)
	{
		free(exp[exp_len]);
		exp_len++;
	}
	free(exp);
	*i = *i + exp_len - 1;
	return (0);
}

char	**content_checker(char ***ref_content, t_shell *shell)
{
	int		i;
	int		j;
	char	**content;

	i = 0;
	j = 0;
	content = *ref_content;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			*ref_content = content;
			return (printf("minishell: syntax error\n"), (NULL));
		}
		if (str_is_alfa_num(content[i]) == false)
		{
			check_expand_content(&content, &i, shell);
			j++;
		}
		i++;
	}
	return (content);
}

bool	arg_expand(char ***ref_content, t_shell *shell)
{
	int		k;
	char	**content;
	char	**new_content;

	content = content_checker(ref_content, shell);
	if (content == NULL)
		return (false);
	k = 0;
	len_loop(content, &k);
	if (k == 0)
	{
		*ref_content = content;
		return (true);
	}
	k = 0;
	len_loop_2(content, &k);
	new_content = n_content_alloc_fill(content, k, shell);
	if (!new_content)
		return (false);
	free_d_str(content);
	*ref_content = new_content;
	return (true);
}
