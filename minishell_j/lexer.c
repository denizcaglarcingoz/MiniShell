#include "minishell.h"

t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type)
{
	t_tokens *new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	//finish protect todo
	c_token->next = new_token;
	new_token->content = ft_strdup(content);
	//protect
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

t_tokens	*token_init_quote(t_tokens *c_token,char **content, t_token_type type)
{
	t_tokens *new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));//finish protect todo
	if (!new_token)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	c_token->next = new_token;
	int i = 0;
	(*content)++;
	while ((*content)[i] != '"')
		i++;
	new_token->content = (char*)malloc(i);
	//protect malloc
	i = 0;
	while((*content)[i] != '"')
	{
		(new_token->content)[i] = (*content)[i];
		i++;
	}
	(new_token->content)[i] = '\0';
	while(**content != '"')
		(*content)++;
	if (!new_token->content)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

t_tokens	*init_initial_token(char **inp)
{
	t_tokens	*c_token;

	c_token = (t_tokens*)malloc(sizeof(t_tokens));
	//protect malloc later
	int i = 0;
	while((*inp)[i] != ' ')
		i++;
	c_token->type = INITIAL; 
	c_token->content = (char *)malloc(i);
	//protect malloc later
	c_token->next = NULL;
	i = 0;
	while((*inp)[i] != ' ')
	{
		(c_token->content)[i] = (*inp)[i];
		i++;
	}
	(c_token->content)[i] = '\0';
	while(**inp != ' ')
		(*inp)++;
	return (c_token);
}

t_tokens	*build_token_list(char *input)
{
		
	t_tokens		*c_token;
	t_tokens		*first_token;
	t_token_type	type;
	char			*token_start;
	int				quotes_pos;
	
	token_start = input;
	quotes_pos = 0;
	//INITIAL TOKEN initilization
	c_token = init_initial_token(&input);
	first_token = c_token;
	while(*input)
	{
		if (*input == ' ' && quotes_pos % 2 == 0)
			input++;
		
		if (*input == '|' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "|", PIPE);
		else if (*input == '<' && *(input + 1) != '<' && *(input - 1) != '<' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "<", LESS);
		else if (*input == '>' && *(input + 1) != '>' && *(input - 1) != '>' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, ">", GREATER);
		else if (*input == '<' && *(input + 1) == '<' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "<<", D_LESS);
		else if (*input == '>' && *(input + 1) == '>'&& quotes_pos % 2 == 0)
			c_token = token_init(c_token, ">>", D_GREATER);
		else if (*input == '(' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "(", L_PAR);
		else if (*input == ')' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, ")", R_PAR);
		else if (*input == '"')
		{	
			quotes_pos++;
			c_token = token_init_quote(c_token, &input, D_QUOTE);
			quotes_pos++;
		}
		else
		{
			type = STRING;
			/* while (*input && !ft_strchr(" |<>()", *input))
				input++;
			input--; */
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