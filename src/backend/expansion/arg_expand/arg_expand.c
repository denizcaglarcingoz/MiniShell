/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:27 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/13 18:35:51 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expand_content(char ***content, int *i, t_shell *shell)
{
	int		exp_len;
	char	**exp;

	exp = exp_check((*content)[*i], shell);//protect here
	*content = split_join((*content), exp, *i, shell);//pro ret null from content_checker on fail
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
			printf("minishell: syntax error\n");
			*ref_content = content;
			return (NULL);
		}
		if (str_is_alfa_num(content[i]) == false)
		{
			if (check_expand_content(&content, &i, shell))
				return (NULL);
			j++;
		}
		i++;
	}
	return (content);
}

char	**n_content_alloc_fill(char **content, int k)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = (char **)malloc(sizeof(char *) * (k + 1));//check pro here
	if (new_content == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new_content[k] = NULL;
	k = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
		{
			new_content[k] = ft_strdup(content[i]);//pro free all prev, use free matrix func.
			k++;
		}
		i++;
	}
	return (new_content);
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
	new_content = n_content_alloc_fill(content, k);
	if (!new_content)
		return (false);
	free_content(content);
	*ref_content = new_content;
	return (true);
}