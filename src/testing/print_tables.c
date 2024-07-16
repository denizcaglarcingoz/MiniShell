/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:31 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/16 17:14:59 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	print_tables(t_table *table)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (table == NULL)
// 		return (0);
// 	while (i < table->table_len)
// 	{
// 		j = 0;
// 		while (table[i].args[j] != NULL)
// 		{
// 			printf("table[%d].args[%d] = %s\n", i, j, table[i].args[j]);
// 			// printf("table[%d].args_len = %zu\n", i, 
// 			// ft_strlen_double(table[i].args));
// 			j++;
// 		}
// 		j = 0;
// 		while (table[i].in[j] != NULL)
// 		{
// 			printf("table[%d].in[%d] = %s\n", i, j, table[i].in[j]);
// 			j++;
// 		}
// 		j = 0;
// 		while (table[i].out[j] != NULL)
// 		{
// 			printf("table[%d].out[%d] = %s\n", i, j, table[i].out[j]);
// 			// printf("table[%d].out_len = %zu\n", i, 
// 			// ft_strlen_double(table[i].out));
// 			j++;
// 		}
// 		j = 0;
// 		while (table[i].append[j] != NULL)
// 		{
// 			printf("table[%d].append[%d] = %s\n", i, j, table[i].append[j]);
// 			j++;
// 		}
// 		j = 0;
// 		while (table[i].heredoc[j] != NULL)
// 		{
// 			printf("table[%d].heredoc[%d] = %s\n", i, j, table[i].heredoc[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return  (0);
// } 