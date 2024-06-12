/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:39 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:29:40 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell)
{
	char	*temp;
	int		new_content_len;
	int		d_exp_len;

	new_content_len = 0;
	while ((*new_content)[new_content_len] != NULL)
		new_content_len++;
	temp = (*new_content)[new_content_len - 1];
	(*new_content)[new_content_len - 1] = \
	ft_strjoin((*new_content)[new_content_len - 1], (*d_exp)[0]);//protect
	free(temp);
	d_exp_len = 0;
	while ((*d_exp)[d_exp_len] != NULL)
		d_exp_len++;
	*joined = (char **)malloc(sizeof(char *) * (new_content_len + d_exp_len + 1));
	if (*joined == NULL)
	{
		free_d_str(*new_content);
		free_d_str(*d_exp);
		free_all(shell, "Malloc Error\n", 127);
	}
}

void	second_loops(char ***new_content, char ***d_exp, char ***joined)
{
	int	d_exp_len;
	int	new_content_len;

	new_content_len = 0;
	while ((*new_content)[new_content_len] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*new_content)[new_content_len]);//pro
		new_content_len++;
	}
	d_exp_len = 0;
	while ((*d_exp)[d_exp_len + 1] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*d_exp)[d_exp_len + 1]);//pro
		new_content_len++;
		d_exp_len++;
	}
	(*joined)[new_content_len] = NULL;
}

char	**add_new_content(char **new_content, char **d_exp, t_shell *shell)
{
	char	**joined;

	if (d_exp == NULL)
		return (new_content);
	if (new_content && new_content[0][0] == '\0' && new_content[1] == NULL)
	{
		free_d_str(new_content);
		return (d_exp);
	}
	first_loops(&new_content, &d_exp, &joined, shell);
	second_loops(&new_content, &d_exp, &joined);
	free_d_str(new_content);
	free_d_str(d_exp);
	return (joined);
}
