#include "minishell.h"

void print_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("content: %s\n", tmp->content);
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
	}
}