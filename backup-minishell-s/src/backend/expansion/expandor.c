#include "minishell.h"

bool content_check(char *content)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
			{	
				if (content[i] == '\'')
					break;
				i++;
			}
			if (!content[i])
				return (false);
		}
		else if (content[i] == '"')
		{
			i++;
			while (content[i] && content[i] != '"')
			{
				if (content[i] == '"')
					break;
				i++;
			}
			if (!content[i])
				return (false);
		}
		i++;
	}
	return (true);
}

bool check_in_expandor(t_table exp_table)
{
	int i;
	
	i = 0;
	while (exp_table.in[i] != NULL)
	{
		if (access(exp_table.in[i], F_OK) == -1)
		{
			printf("bash: %s: syntax error: no such file\n", exp_table.in[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	expandor(t_shell *shell, int table_num)
{
	if (arg_expand(&(shell->tables[table_num].args), shell) == false ||
		redir_expand(shell->tables[table_num].in, shell) == false ||
		redir_expand(shell->tables[table_num].out, shell) == false ||
		redir_expand(shell->tables[table_num].append, shell) == false ||
		check_in_expandor(shell->tables[table_num]) == false)
	{
		free_all(shell, "no print", 0);
		return (false);
	}
	return (true);
}

// typedef struct s_tokens
// {
// 	t_token_type	type;
// 	char			*content;
// 	struct s_tokens	*next;
// }	t_tokens;