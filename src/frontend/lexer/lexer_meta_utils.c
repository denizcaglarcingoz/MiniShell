/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_meta_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:17 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 02:13:26 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type)
{
	t_tokens	*new_token;

	new_token = NULL;
	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	new_token->content = ft_strdup(content);
	new_token->type = type;
	new_token->next = NULL;
	if (new_token->content == NULL)
		return (NULL);
	return (new_token);
}

t_tokens	*meta_content(t_tokens *c_token, char **input)
{
	if (**input == '|')
		c_token = token_init(c_token, "|", PIPE);
	else if (**input == '<' && *(*input + 1) != '<')
		c_token = token_init(c_token, "<", LESS);
	else if (**input == '>' && *(*input + 1) != '>')
		c_token = token_init(c_token, ">", GREATER);
	else if (**input == '<' && *(*input + 1) == '<')
	{
		c_token = token_init(c_token, "<<", D_LESS);
		(*input)++;
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		c_token = token_init(c_token, ">>", D_GREATER);
		(*input)++;
	}
	return (c_token);
}
