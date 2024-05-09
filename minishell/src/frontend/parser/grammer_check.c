#include "minishell.h"

t_tokens *error_print(t_tokens *tokens)
{
	if (tokens == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
	}
	else
		printf("syntax error near unexpected token '%s'\n", tokens->content);
	return (NULL);
}

t_tokens *grammer_check(t_tokens *tokens)
{
	t_tokens *first_token;

	if (tokens == NULL)
		return (NULL);
	first_token = tokens;
	if (tokens->type == PIPE)
		return (error_print(tokens));
	while(tokens)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL || tokens->next->type == PIPE)
				return (error_print(tokens));
		}
		else if (tokens->type == GREATER || tokens->type == D_GREATER ||
				tokens->type == LESS || tokens->type == D_LESS)
		{
			tokens = tokens->next;
			if (tokens == NULL || tokens->type != STRING)
				return (error_print(tokens));
		}
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (first_token);
}
