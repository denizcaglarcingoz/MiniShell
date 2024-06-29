/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:25 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 00:00:37 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_first_entry(t_tokens *c_token, t_tokens **first_token, \
int *first_entry)
{
	if (*first_entry == 1)
	{
		*first_token = c_token;
		(*first_entry)++;
	}
}

static void	err_exit(t_tokens *first_token, t_shell *shell)
{
	free_list(first_token);
	token_list_error_exit(shell);
}

t_tokens	*build_token_list(char *input, t_shell *shell)
{
	t_tokens	*c_token;
	t_tokens	*first_token;
	int			first_entry;

	if (input[0] == '\0')
		return (NULL);
	first_entry = 1;
	c_token = NULL;
	first_token = NULL;
	while (*input)
	{
		if (*input == '|' || *input == '<' || *input == '>')
			c_token = meta_content(c_token, &input);
		else if (*input != ' ' && *input != 8 && *input != 9 && *input != 10 \
		&& *input != 11 && *input != 12 && *input != 13)
			c_token = token_init_string(c_token, &input, STRING);
		handle_first_entry(c_token, &first_token, &first_entry);
		if (c_token == NULL)
			break ;
		input++;
	}
	if (c_token == NULL)
		err_exit(first_token, shell);
	return (first_token);
}
