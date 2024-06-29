/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:55 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 18:21:52 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dollar_question(t_shell *shell)
{
	char	**new_d_exp;

	new_d_exp = (char **)malloc(sizeof(char *) * 2);
	new_d_exp[0] = ft_itoa(shell->exit_status);
	if (new_d_exp == 0)
		free_all(shell, "Malloc Error\n", 127);
	new_d_exp[1] = NULL;
	return (new_d_exp);
}

char	*quo_dollar_question(int *i, char *new_cntnt, t_shell *shell)
{
	char	*exp;
	char	*temp;

	temp = new_cntnt;
	(*i)++;
	exp = ft_itoa(shell->exit_status);
	if (exp == 0)
		return (NULL);
	new_cntnt = ft_strjoin(new_cntnt, exp);
	free(exp);
	if (new_cntnt == NULL)
		return (NULL);
	free(temp);
	return (new_cntnt);
}
