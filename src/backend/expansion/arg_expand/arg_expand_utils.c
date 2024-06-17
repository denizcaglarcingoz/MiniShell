/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:21 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 23:56:19 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	len_loop(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) == 0)
			(*k)++;
		i++;
	}
}

void	len_loop_2(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i][0] == '\0')
		{
			// ft_putchar_fd('I', 1);
			// ft_putnbr_fd(i, 1);
			// ft_putchar_fd(content[i][1], 1);
			// ft_putchar_fd('\n', 1);
			if (content[i][1] == '"')
			{
				// write(1, "XERE\n", 5);	
				(*k)++;
			}
		}
		else
		{	
			(*k)++;
		}
		i++;
		// write(1, "HERE\n", 5);
	}
}

void	free_content(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
	content = NULL;
}
