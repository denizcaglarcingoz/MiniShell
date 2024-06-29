/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:26:19 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 00:08:15 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	*parser(t_tokens *tokens, t_shell *shell)
{
	t_table		*table;

	table = NULL;
	if (tokens == NULL)
		return (NULL);
	table = table_alloc(tokens, shell);
	table = table_init(tokens, table, shell);
	return (table);
}

size_t	ft_strlen_double(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
