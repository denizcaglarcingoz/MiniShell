#include "minishell.h"

void	free_list(t_tokens *tokens)
{
	t_tokens	*temp;

	if (tokens == NULL)
		return ;
	while (tokens)
	{
		temp = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = temp;
	}
	tokens = NULL;
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (0);
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
