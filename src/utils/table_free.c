/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:24:58 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:25:00 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	if (table == NULL)
		return ;
	while (table[i].args != NULL)
	{
		free_d_str(table[i].args);
		free_d_str(table[i].in);
		free_d_str(table[i].out);
		free_d_str(table[i].append);
		free_d_str(table[i].heredoc);
		i++;
	}
	free(table);
	table = NULL;
}
