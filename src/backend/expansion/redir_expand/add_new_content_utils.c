/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_content_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 06:01:03 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 06:08:08 by dcingoz          ###   ########.fr       */
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
