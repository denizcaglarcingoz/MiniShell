/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:49 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 17:34:06 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_in(t_table table)
{
	int	i;

	if (table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (table.in[i] != NULL)
	{
		if (access(table.in[i], F_OK) == -1)
			return (NULL);
		i++;
	}
	return (table.in[i - 1]);
}

void	execution(t_shell *shell)
{
	if (shell->tables == NULL)
		return ;
	shell->table_len = shell->tables->table_len;
	if (shell->tables->table_len < 2)
		single_exec(shell);
	else
		pipe_execution(shell);
}
