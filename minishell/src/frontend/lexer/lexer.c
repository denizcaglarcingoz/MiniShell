#include "minishell.h"

t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type)
{
	t_tokens *new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	//protect todo
	c_token->next = new_token;
	new_token->content = ft_strdup(content);
	//protect
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

t_tokens	*token_init_string(t_tokens *c_token,char **content, t_token_type type)
{
	t_tokens	*new_token;
	int			d_quo_quant;
	int			quo_quant;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	//protect todo
	c_token->next = new_token;
	int i = 0;

	quo_quant = 0;
	d_quo_quant = 0;
	while (1)
	{
		if((*content)[i] == '\0')
			break ;
		if((*content)[i] == '"')
		{
			d_quo_quant++;
			if(d_quo_quant == 2)
			{
				d_quo_quant = 0;
				if(quo_quant % 2 == 1)
					quo_quant = 0;
			}
		}
		if((*content)[i] == '\'')
			quo_quant++;
		if((*content)[i] == ' ' && d_quo_quant % 2 == 0  && quo_quant % 2 == 0)
			break ;
		if(is_meta_char((*content)[i]) == true && d_quo_quant %2 == 0 && quo_quant % 2 == 0)
			break ;
		i++;
	}
	new_token->content = (char*)malloc(i);
	//protect malloc
	i = 0;
	d_quo_quant = 0;
	quo_quant = 0;
	while(1)
	{
		if((*content)[i] == '\0')
			break ;
		if((*content)[i] == '"')
		{
			d_quo_quant++;
			if(d_quo_quant == 2)
			{
				d_quo_quant = 0;
				if(quo_quant % 2 == 1)
					quo_quant = 0;
			}
		}
		if((*content)[i] == '\'')
			quo_quant++;
		if((*content)[i] == ' ' && d_quo_quant % 2 == 0  && quo_quant % 2 == 0)
			break ;
		if(is_meta_char((*content)[i]) == true && d_quo_quant % 2 == 0 && quo_quant % 2 == 0)
			break ;
		(new_token->content)[i] = (*content)[i];
		i++;
	}
	(new_token->content)[i] = '\0';
	d_quo_quant = 0;
	quo_quant = 0;
	while(1)
	{
		if(**content == '\0')
			break ;
		if(**content == '"')
		{
			d_quo_quant++;
			if(d_quo_quant == 2)
			{
				d_quo_quant = 0;
				if(quo_quant % 2 == 1)
					quo_quant = 0;
			}
		}
		if(**content == '\'')
			quo_quant++;
		if (**content == ' ' && d_quo_quant % 2 == 0  && quo_quant % 2 == 0)
			break ;
		if(is_meta_char(**content) == true && d_quo_quant % 2 == 0 && quo_quant % 2 == 0)
			break ;
		(*content)++;
	}
	(*content)--;
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}

t_tokens	*init_initial_token()//char **inp)
{
	t_tokens	*c_token;

	c_token = (t_tokens*)malloc(sizeof(t_tokens));
	//protect malloc later
	// int i = 0;
	// while((*inp)[i] != ' ')
	// 	i++;
	// c_token->type = INITIAL; 
	// c_token->content = (char *)malloc(i);
	// //protect malloc later
	// c_token->next = NULL;
	// i = 0;
	// while((*inp)[i] != ' ')
	// {
	// 	(c_token->content)[i] = (*inp)[i];
	// 	i++;
	// }
	// (c_token->content)[i] = '\0';
	// while(**inp != ' ')
	// 	(*inp)++;
	return (c_token);
}

t_tokens	*build_token_list(char *input)
{
		
	t_tokens		*c_token;
	t_tokens		*first_token;
	//char			*token_start;
	int				quotes_pos;
	int				first_entry;

	first_entry = 1;
	//token_start = input;
	quotes_pos = 0;
	//INITIAL TOKEN initilization
	c_token = init_initial_token();//&input);
	first_token = c_token;
	while(*input)
	{
		if (*input == ' ' && quotes_pos % 2 == 0)
			input++;
		
		if (*input == '|' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "|", PIPE);
		else if (*input == '<' && *(input + 1) != '<' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, "<", LESS);
		else if (*input == '>' && *(input + 1) != '>' && quotes_pos % 2 == 0)
			c_token = token_init(c_token, ">", GREATER);
		else if (*input == '<' && *(input + 1) == '<' && quotes_pos % 2 == 0)
		{
			c_token = token_init(c_token, "<<", D_LESS);
			input++;
		}
		else if (*input == '>' && *(input + 1) == '>'&& quotes_pos % 2 == 0)
		{
			c_token = token_init(c_token, ">>", D_GREATER);
			input++;	
		}
		else if (*input != ' ')
		{
			quotes_pos++;
			c_token = token_init_string(c_token, &input, D_QUOTE);
			quotes_pos++;
		}
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