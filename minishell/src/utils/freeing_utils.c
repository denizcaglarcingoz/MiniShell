#include "minishell.h"

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
/* void	free_list(t_tokens **tokens)
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
		curr->content = NULL;
		free(curr);
		curr = temp;
	}
	*tokens = NULL;
} */

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	free_matrix(char **matrix, int i)
{
	while (--i >= 0)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i--;
	}
	free(matrix);
	matrix = NULL;
}

void	free_t_content_alloc_and_table(t_table *table, int i)
{
	while (--i >= 0)
	{
	if (table[i].args)
		free_matrix(table[i].args, ft_matrix_len(table[i].args));
	if (table[i].in)
		free_matrix(table[i].in, ft_matrix_len(table[i].in));
	if (table[i].out)
		free_matrix(table[i].out, ft_matrix_len(table[i].out));
	if (table[i].append)	
		free_matrix(table[i].append, ft_matrix_len(table[i].append));
	if (table[i].heredoc)
		free_matrix(table[i].heredoc, ft_matrix_len(table[i].heredoc));
	}
	free(table);
	table = NULL;
}

void	free_content_first_allocs_only(t_table table)//do i need this?
{
	free(table.args);
	free(table.in);
	free(table.out);
	free(table.append);	
	free(table.heredoc);
}
