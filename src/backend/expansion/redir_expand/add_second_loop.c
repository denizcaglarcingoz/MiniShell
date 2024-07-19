/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_second_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 06:00:03 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 06:07:58 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	d_exp_len_init(t_shell *shell)
{
	int	d_exp_len;

	if (shell->exp_space_flag_start == 1)
		d_exp_len = -1;
	else
		d_exp_len = 0;
	return (d_exp_len);
}

void	sec_loop_joined_finalize(char ***joined, \
t_shell *shell, int new_content_len)
{
	if (shell->exp_space_flag_end == 1)
	{
		(*joined)[new_content_len] = empty_txt_nothing();
		(*joined)[new_content_len + 1] = NULL;
	}
	else
		(*joined)[new_content_len] = NULL;
}

void	second_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell)
{
	int	d_exp_len;
	int	new_content_len;

	new_content_len = 0;
	while ((*new_content)[new_content_len] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*new_content)[new_content_len]);
		if ((*joined)[new_content_len] == NULL && free_d_str_int(*d_exp))
			joined_free(joined, shell, new_content_len, *new_content);
		new_content_len++;
	}
	d_exp_len = d_exp_len_init(shell);
	while ((*d_exp)[d_exp_len + 1] != NULL)
	{
		(*joined)[new_content_len] = ft_strdup((*d_exp)[d_exp_len + 1]);
		if ((*joined)[new_content_len] == NULL && free_d_str_int(*d_exp))
			joined_free(joined, shell, new_content_len, *new_content);
		new_content_len++;
		d_exp_len++;
	}
	sec_loop_joined_finalize(joined, shell, new_content_len);
}
