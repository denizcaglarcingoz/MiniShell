/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:06:33 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/16 20:08:51 by dcingoz          ###   ########.fr       */
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

void	shell_hdoc_init(t_shell *shell)
{
	shell->hdoc = (char **)malloc(sizeof(char *) * (shell->table_len + 1));
	if (shell->hdoc == NULL)
		free_all(shell, "malloc fail", 127);
	shell->hdoc[shell->table_len] = NULL;
}

int	pipe_hdocs(t_shell *shell)
{
	int		i;
	char	*non_exp_hdoc;

	if (is_hdoc_exist(shell) == 0)
		return (0);
	shell_hdoc_init(shell);
	i = 0;
	while (i < shell->table_len)
	{
		if (expandor_hdoc(shell, i) == false)
			return (1);
		non_exp_hdoc = get_last_non_exp_hdoc(shell->tables[i], shell);
		if (shell->tables[i].heredoc[0] == NULL)
			shell->hdoc[i] = ft_strdup("");
		else
		{
			shell->hdoc[i] = check_hdoc_p(shell->tables[i], shell);
			shell->hdoc[i] = hdoc_in_exp(shell, shell->hdoc[i], non_exp_hdoc);
		}
		if (g_sig_int == SIGUSR1)
			return (free_all(shell, "", 0), 1);
		i++;
	}
	return (0);
}
