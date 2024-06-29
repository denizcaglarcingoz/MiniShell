/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:03 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:33:49 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *shell)
{
	shell->exit_status = 0;
	shell->env = get_env();
	if (!shell->env)
		exit(EXIT_FAILURE);
	shell->exported = get_env();
	if (!shell->exported)
	{
		free_all_env(shell->env);
		exit(EXIT_FAILURE);
	}
	ft_quicksort_params(shell->exported, 0, ft_matrix_len(shell->exported) - 1);
}
