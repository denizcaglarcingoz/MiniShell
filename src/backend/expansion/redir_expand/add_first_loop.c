/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_first_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 05:59:14 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 06:07:20 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	n_content_fail(char ***new_content, char ***d_exp, t_shell *shell)
{
	free_d_str(*new_content);
	free_d_str(*d_exp);
	free_all(shell, "Malloc Error\n", 127);
}

void	f_loops_joined_malloc(char ***joined, int d_exp_len, t_shell *shell)
{
	if (shell->exp_space_flag_start != 1 && shell->exp_space_flag_end != 1)
		*joined = (char **)malloc(sizeof(char *) * (d_exp_len + 1));
	if (shell->exp_space_flag_start == 1 || shell->exp_space_flag_end == 1)
	{
		if (shell->exp_space_flag_start == 1 && shell->exp_space_flag_end == 1)
			*joined = (char **)malloc(sizeof(char *) * (d_exp_len + 3));
		else
			*joined = (char **)malloc(sizeof(char *) * (d_exp_len + 2));
	}
}

void	first_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell)
{
	int		new_c_len;
	int		d_exp_len;
	char	*temp;

	new_c_len = d_str_len(*new_content);
	temp = (*new_content)[new_c_len - 1];
	if (shell->exp_space_flag_start != 1)
	{
		(*new_content)[new_c_len - 1] = \
		ft_strjoin((*new_content)[new_c_len - 1], (*d_exp)[0]);
		free(temp);
	}
	if ((*new_content)[new_c_len - 1] == NULL)
		n_content_fail(new_content, d_exp, shell);
	d_exp_len = d_str_len(*d_exp);
	f_loops_joined_malloc(joined, d_exp_len, shell);
	if (*joined == NULL)
		n_content_fail(new_content, d_exp, shell);
}
