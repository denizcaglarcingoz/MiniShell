#include "minishell.h"

int init_loop(char **content, int d_quo_qty, int quo_qty, int i)
{
	while (1)
	{
		if ((*content)[i] == '\0')
			break ;
		if ((*content)[i] == '"')
		{
			d_quo_qty++;
			if(d_quo_qty == 2)
			{
				d_quo_qty = 0;
				if(quo_qty % 2 == 1)
					quo_qty = 0;
			}
		}
		if ((*content)[i] == '\'')
			quo_qty++;
		if ((*content)[i] == ' ' && d_quo_qty % 2 == 0  && quo_qty % 2 == 0)
			break ;
		if (is_meta_char((*content)[i]) == true && d_quo_qty %2 == 0 && quo_qty % 2 == 0)
			break ;
		i++;
	}
	return (i);
}

t_tokens	*token_init_string(t_tokens *c_token,char **content, t_token_type type)
{
	t_tokens	*new_token;
	int			i;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	i = init_loop(content, 0, 0, 0);
	new_token->content = (char*)malloc(i + 1);
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
