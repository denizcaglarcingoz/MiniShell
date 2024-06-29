/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_loop_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:46:58 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/28 19:09:02 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_dquo(int *first_quo, int *d_quo_qty)
{
	if (*first_quo == 0)
		*first_quo = 1;
	(*d_quo_qty)++;
}

void	if_squo(int *first_quo, int *quo_qty)
{
	if (*first_quo == 0)
		*first_quo = 2;
	(*quo_qty)++;
}

int	if_wspace(int first_quo, int quo_qty, int d_quo_qty)
{
	if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
		return (1);
	if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
		return (1);
	if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
		return (1);
	return (0);
}

int	if_quo_null(int first_quo, int quo_qty, int d_quo_qty, int *i)
{
	(*i)++;
	if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
		return (1);
	if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
		return (1);
	if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
		return (1);
	return (0);
}

int	if_meta(int first_quo, int quo_qty, int d_quo_qty)
{
	if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
		return (1);
	if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
		return (1);
	if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
		return (1);
	return (0);
}
