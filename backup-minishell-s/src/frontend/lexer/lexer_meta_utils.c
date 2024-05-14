#include "minishell.h"

t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type)
{
	t_tokens *new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if(new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	new_token->content = ft_strdup(content);
	if (new_token->content == NULL)
	{	
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

t_tokens *meta_content(t_tokens *c_token, char **input)
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
