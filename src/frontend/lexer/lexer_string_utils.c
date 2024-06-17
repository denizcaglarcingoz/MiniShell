/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:21 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 16:31:39 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_loop(char **content, int d_quo_qty, int quo_qty, int i)
{
	int	first_quo;

	first_quo = 0;
	while (1)
	{
		if ((*content)[i] == '\0')
			break ;
		if ((*content)[i] == '"')
			if_dquo(&first_quo, &d_quo_qty);
		if ((*content)[i] == '\'')
			if_squo(&first_quo, &quo_qty);
		if (is_white_space((*content)[i]) == true)
			if (if_wspace(first_quo, quo_qty, d_quo_qty))
				break ;
		if (((*content)[i] == '\'' || (*content)[i] == '"') \
		&& (content[0][i + 1] == '\0' \
		|| is_white_space(content[0][i + 1]) == true))
			if (if_quo_null(first_quo, quo_qty, d_quo_qty, &i))
				break ;
		if (is_meta_char((*content)[i]) == true)
			if (if_meta(first_quo, quo_qty, d_quo_qty))
				break ;
		i++;
	}
	return (i);
}

t_tokens	*token_init_string(t_tokens *c_token, char **content, \
t_token_type type)
{
	t_tokens	*new_token;
	int			i;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	i = init_loop(content, 0, 0, 0);
	new_token->content = (char *)malloc(i + 1);
	if (new_token->content == NULL)
	{
		free(new_token);
		return (NULL);
	}
	ft_strlcpy(new_token->content, *content, i + 1);
	while (i > 0)
	{
		(*content)++;
		i--;
	}
	(*content)--;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}
