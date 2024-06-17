/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:27 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 23:59:26 by dcingoz          ###   ########.fr       */
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

	
	// -----------
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
	// -----------
	// int k = 0;

	// write(1, "after split join\n", 17);
	
	// while ((content)[k] != NULL)
	// {
	// 	write(1, &((content)[0][0]), 1);
	// 	write(1, "1 ", 2);
	// 	if ((content)[0][1] != '\0')
	// 	{
	// 		write(1, "2", 1);
	// 		write(1, &((content)[0][1]), 1);
	// 		write(1, "2 ", 2);
	// 		if ((content)[0][2] == '\0')
	// 		{
	// 			write(1, "3", 1);
	// 			write(1, &(content[0][2]), 1);
	// 			write(1, "3\n", 2);
	// 		}
	// 	}	
	// 	k++;
	// }

	// -----------
	return (content);
}

char	**n_content_alloc_fill(char **content, int k)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = (char **)malloc(sizeof(char *) * (k + 1));//check pro here
	// ft_putchar_fd('k', 1);
	// ft_putnbr_fd(k, 1);
	// ft_putchar_fd('\n', 1);
	if (new_content == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new_content[k] = NULL;
	k = 0;
	while (content[i])
	{
		if (content[i][0] == '\0')
		{
			if (content[i][1] == '"')
			{
				// write(1, "here\n", 5);
				new_content[k] = ft_strdup("");
				k++;
			}
		}
		else	
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
	// if (content[0][0] == '\0')
	// {
	// 	write(1, "contetn", 6);
	// 	write(1, &(content[0][0]), 1);
	// 	write(1, "1\n", 2);
	// 	if (content[0][1] != '\0')
	// 	{
	// 		write(1, "content", 6);
	// 		write(1, &(content[0][1]), 1);
	// 		write(1, "2\n", 2);
	// 		if (content[0][2] == '\0')
	// 		{
	// 			write(1, "content", 6);
	// 			write(1, &(content[0][2]), 1);
	// 			write(1, "3\n", 2);
	// 		}
	// 	}
	// }
	// ft_putchar_fd('k', 1);
	// ft_putnbr_fd(k, 1);
	// ft_putchar_fd('\n', 1);
	new_content = n_content_alloc_fill(content, k);
	if (!new_content)
		return (false);
	free_content(content);
	*ref_content = new_content;
	return (true);
}