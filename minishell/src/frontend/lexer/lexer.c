#include "minishell.h"

t_tokens	*build_token_list(char *input)
{		
	t_tokens		*c_token;
	t_tokens		*first_token;
	int				first_entry;

	first_entry = 1;
	c_token = NULL;
	first_token = NULL;
	while(*input)
	{
		if (*input == '|' || *input == '<' || *input == '>')
			c_token = meta_content(c_token, &input);
		else if (*input != ' ')
			c_token = token_init_string(c_token, &input, STRING);
		if(c_token == NULL)
			return (NULL);
		if (first_entry == 1)
		{
			first_token = c_token;
			first_entry++;
		}
		input++;
	}
	return (first_token);
}
//testing---------------------------------
void	print_tokens(t_tokens *tokens)
{
	while (1) 
	{
		if (tokens == NULL)
		{
			printf("last token\n");
			break;
		}
		printf(" TOKEN TYPE: %d\n TOKEN CONTENT: %s\n", tokens->type, tokens->content);
		printf("strlen: %lu\n\n", strlen(tokens->content));
		if (tokens == NULL)
			break;
		tokens = tokens->next;
	}
}