#include "/home/dcingoz/CC/minishell/minishell/includes/minishell.h"

void	free_list(t_tokens *tokens)
{
	t_tokens	*curr;
	t_tokens	*temp;

	if (tokens == NULL)
		return ;
	curr = tokens;
	while (curr)
	{
		temp = curr->next;
		free(curr->content);
		free(curr);
		curr = temp;
	}
	tokens = NULL;
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
