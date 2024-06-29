/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:39 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 20:08:42 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	joined_free(char ***joined, t_shell *shell, \
int new_content_len, char **new_content)
{
	int	i;

	i = 0;
	while (i < new_content_len)
	{
		free((*joined)[i]);
		i++;
	}
	free_d_str(new_content);
	free(*joined);
	free_all(shell, "Malloc Error\n", 127);
}

int	free_d_str_int(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (1);
}

void	second_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell)
{
	int	d_exp_len;
	int	new_content_len;

	new_content_len = 0;
	while ((*new_content)[new_content_len] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*new_content)[new_content_len]);
		if ((*joined)[new_content_len] == NULL && free_d_str_int(*d_exp))
			joined_free(joined, shell, new_content_len, *new_content);
		new_content_len++;
	}
	d_exp_len = 0;
	while ((*d_exp)[d_exp_len + 1] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*d_exp)[d_exp_len + 1]);
		if ((*joined)[new_content_len] == NULL && free_d_str_int(*d_exp))
			joined_free(joined, shell, new_content_len, *new_content);
		new_content_len++;
		d_exp_len++;
	}
	(*joined)[new_content_len] = NULL;
}

void	first_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell)
{
	int		new_c_len;
	int		d_exp_len;
	char	*temp;

	new_c_len = d_str_len(*new_content);
	temp = (*new_content)[new_c_len - 1];
	(*new_content)[new_c_len - 1] = \
	ft_strjoin((*new_content)[new_c_len - 1], (*d_exp)[0]);
	if ((*new_content)[new_c_len - 1] == NULL)
	{
		free_d_str(*new_content);
		free_d_str(*d_exp);
		free_all(shell, "Malloc Error\n", 127);
	}
	free(temp);
	d_exp_len = d_str_len(*d_exp);
	*joined = (char **)malloc(sizeof(char *) * (new_c_len + d_exp_len + 1));
	if (*joined == NULL)
	{
		free_d_str(*new_content);
		free_d_str(*d_exp);
		free_all(shell, "Malloc Error\n", 127);
	}
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
	second_loops(&new_content, &d_exp, &joined, shell);
	free_d_str(new_content);
	free_d_str(d_exp);
	return (joined);
}
