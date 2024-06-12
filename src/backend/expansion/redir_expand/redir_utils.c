/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:56:35 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 22:05:28 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_exp_fail(char **new_cntnt, char *cntnt, t_shell *shell)
{
	free(cntnt);
	free_d_str(new_cntnt);
	free_all(shell, "Malloc Error\n", 127);
}
