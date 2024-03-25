#include "/home/dcingoz/CC/minishell/minishell/includes/minishell.h"

void	free_list(t_tokens **tokens)
{
	t_tokens	*curr;
	t_tokens	*temp;

	if (tokens == NULL)
		return ;
	curr = *tokens;
	while (curr)
	{
		temp = curr->next;
		free(curr->content);
		free(curr);
		curr = temp;
	}
	*tokens = NULL;
}

int	ft_size(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		tokens = tokens->next;
		count++;
	}
	return (count);
}

t_tokens	*ft_last(t_tokens *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

void	add_token(t_tokens **tokens, t_tokens *newnode)
{
	t_tokens	*curr;
	
	if (tokens == NULL || newnode == NULL)
		return ;
	if (*tokens == NULL)
	{
		*tokens = newnode;
		return ;
	}
	curr = *tokens;
	while (curr->next)
		curr = curr->next;
	curr->next = newnode;
}

/* void	add_node(t_tokens **tokens, char **av, t_token_type content)
{
	t_tokens	*newnode;
	t_tokens	*last;

	if (tokens == NULL)
		return ;
	newnode = malloc(sizeof(t_tokens));
	if (newnode == NULL)
		//free_all(tokens);//clean free and exit here
	newnode->next = NULL;
	newnode->content = n;
	if (*tokens == NULL)
	{
		*tokens = newnode;
		newnode->prev = NULL;
	}
	else
	{
		last = ft_last(*tokens);
		last->next = newnode;
		newnode->prev = last;
	}
} */