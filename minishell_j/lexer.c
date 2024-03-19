#include "minishell.h"

t_token	*make_token(char *content, t_token_type type)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));//finish protect todo
	if (!new_token)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

/* 	WHITESPACE,
	PIPE,
	LESS,
	GREATER,
	D_LESS,
	D_GREATER,
	L_PAR,
	R_PAR,
	STRING */

void	build_token_list(char *input)
{
		
	t_tokens *tokens;
	t_token_type type;
	char *token_start;
	
	token_start = input;
	tokens = NULL;
	while(*input)
	{
		if (ft_strchr(, *input))
		{
			if (input != token_start)
			{
			*input = '\0';/* new = (t_tokens *)malloc(sizeof(t_tokens));
		if (new == NULL)
		{
			free_list(tokens);
			free(input);
			ft_putstr_color_fd(2, "Malloc Error", BOLD_RED);
			exit(EXIT_FAILURE);
		}		
		//printf("inp:%s\n",input);
		new->content = ft_strdup(input);
		if (new == NULL)
		{
			free_list(tokens);
			free(input);
			ft_putstr_color_fd(2, "Malloc Error", BOLD_RED);
			exit(EXIT_FAILURE);
		}		 */
		if (*input == ' ')
			type = WHITESPACE; 
		else if (*input == '|')
			type = PIPE;
		else if (*input == '<' && *(input + 1) != '<')
			type = LESS;
		else if (*input == '>' && *(input + 1) != '>')
			type = GREATER;
		else if (*input == '<' && *(input + 1) == '<')
		{
			type = D_LESS;
			input++;
		}
		else if (*input == '>' && *(input + 1) == '>')
		{
			type = D_GREATER;
			input++;
		}
		else if (*input == '(')
			type = L_PAR; 
		else if (*input == ')')
			type = R_PAR;
		else
		{
			type = STRING;
			/* while (*input && !ft_strchr(" |<>()", *input))
				input++;
			input--; */
		}
	add_token(tokens, make_token(&tokens, token_start, type));
	token_start = input + 1;	
	input++;
	}
	return (tokens);
}
//testing---------------------------------
void	print_tokens(t_token *tokens)
{
	while (tokens) 
	{
		printf(" TOKEN TYPE: %d\n TOKEN CONTENT: %c\n\n", tokens->type, tokens->content);
		tokens = (*temp)->next;
	}
}