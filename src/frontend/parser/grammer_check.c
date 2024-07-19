/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammer_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:26:14 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 06:29:26 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*error_print(t_tokens *tokens, t_tokens *first_token)
{
	if (tokens == NULL)
	{
		strerror(2);
		ft_putstr_fd("syntax error near "\
		"unexpected token 'newline'\n", 2);
		free_list(first_token);
	}
	else
	{
		strerror(2);
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(tokens->content, 2);
		ft_putstr_fd("'\n", 2);
		free_list(first_token);
	}
	return (NULL);
}

t_tokens	*grammer_check(t_tokens *tokens, int *exit_status)
{
	t_tokens	*first_token;

	if (tokens == NULL)
		return (NULL);
	first_token = tokens;
	if (tokens->type == PIPE)
		return (*exit_status = 2, error_print(tokens, first_token));
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL || tokens->next->type == PIPE)
				return (*exit_status = 2, error_print(tokens, first_token));
		}
		else if (tokens->type == GREATER || tokens->type == D_GREATER \
		|| tokens->type == LESS || tokens->type == D_LESS)
		{
			tokens = tokens->next;
			if (tokens == NULL || tokens->type != STRING)
				return (*exit_status = 2, error_print(tokens, first_token));
		}
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (first_token);
}

t_tokens	*token_content_check(t_tokens *tokens, int *exit_status)
{
	t_tokens	*first_token;

	if (tokens == NULL)
		return (NULL);
	first_token = tokens;
	while (tokens)
	{
		if (content_check(tokens->content) == false)
			return (*exit_status = 2, error_print(tokens, first_token));
		tokens = tokens->next;
	}
	return (first_token);
}
