/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:21 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 00:06:04 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// f_quo means first_quo
// d_qty means double quote quantity
// s_qty means single quote quantity

int	init_loop(char **inp, int d_qty, int s_qty, int i)
{
	int	f_quo;

	f_quo = 0;
	while ((*inp)[i] != '\0')
	{
		if ((*inp)[i] == '"')
			if_dquo(&f_quo, &d_qty);
		if ((*inp)[i] == '\'')
			if_squo(&f_quo, &s_qty);
		if (is_white_space((*inp)[i]) == true)
			if (if_wspace(f_quo, s_qty, d_qty))
				break ;
		if (((*inp)[i] == '\'' || (*inp)[i] == '"') && (inp[0][i + 1] == '\0' \
		|| is_white_space(inp[0][i + 1]) == true))
			if (if_quo_null(f_quo, s_qty, d_qty, &i))
				break ;
		if (is_meta_char((*inp)[i]) == true)
			if (if_meta(f_quo, s_qty, d_qty))
				break ;
		if ((*inp)[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

t_tokens	*token_init_string(t_tokens *c_token, char **inp, \
t_token_type type)
{
	t_tokens	*new_token;
	int			i;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	i = init_loop(inp, 0, 0, 0);
	new_token->content = (char *)malloc(i + 1);
	if (new_token->content == NULL)
	{
		free(new_token);
		return (NULL);
	}
	ft_strlcpy(new_token->content, *inp, i + 1);
	while (i > 0)
	{
		(*inp)++;
		i--;
	}
	(*inp)--;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}
