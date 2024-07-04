/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_d_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:25:23 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 20:30:16 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_d_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_d_str_till(char **content, int i)
{
	if (!content)
		return ;
	while (i >= 0)
	{
		free(content[i]);
		i--;
	}
	free(content);
}
