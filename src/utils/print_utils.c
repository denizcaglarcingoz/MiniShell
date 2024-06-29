/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:03:34 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/24 22:13:39 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_d_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	write(1, "print_d_str\n", 12);
	while (str[i] != NULL)
	{
		printf("i: %d\n", i);
		printf("str[%d] = %s--\n", i, str[i]);
		i++;
	}
}
