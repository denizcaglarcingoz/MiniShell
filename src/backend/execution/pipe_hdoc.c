/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:06:33 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 01:10:35 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_hdoc_exist(t_shell *shell)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (i < shell->table_len)
	{
		if (shell->tables[i].heredoc[0] != NULL)
			k++;
		i++;
	}
	if (k == 0)
		return (0);
	return (1);
}

int	pipe_hdocs(t_shell *shell)
{
	int	i;

	if (is_hdoc_exist(shell) == 0)
		return (0);
	shell->hdoc = (char **)malloc(sizeof(char *) * (shell->table_len + 1));
	if (shell->hdoc == NULL)
		free_all(shell, "malloc fail", 127);
	shell->hdoc[shell->table_len] = NULL;
	i = 0;
	while (i < shell->table_len)
	{
		if (expandor_hdoc(shell, i) == false)
			return (1);
		if (shell->tables[i].heredoc[0] == NULL)
			shell->hdoc[i] = ft_strdup("");
		else
			shell->hdoc[i] = check_hdoc_p(shell->tables[i], shell);
		if (g_sig_int == SIGUSR1)
			return (free_all(shell, "", 0), 1);
		i++;
	}
	return (0);
}
