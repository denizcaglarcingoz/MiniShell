#include "minishell.h"

char	*expand(char *exp, t_shell *shell)//shell
{
	char	*new_exp;
	int		i;
	//char	**env;

	//env = get_full_env(0);
	i = 0;
	exp = ft_strjoin_char(exp, '=');
	new_exp = ft_strdup("");
	while (shell->env[i])
	{
		if (ft_strncmp(exp, shell->env[i], ft_strlen(exp)) == 0)
		{
			new_exp = ft_strjoin(new_exp, shell->env[i] + ft_strlen(exp));
		}
		i++;
	}
	free(exp);
	return (new_exp);
}

char	*expansion_dollar(char *content, int *i, char *new_content, t_shell *shell)//shell
{
	char	*exp;

	exp = ft_strdup("");
	(*i)++;
	while (content[*i] && is_alfa_num(content[*i]) == true)
	{
		exp = ft_strjoin_char(exp, content[*i]);
		(*i)++;
	}
	exp = expand(exp, shell);
	new_content = ft_strjoin(new_content, exp);
	free(exp);
	return (new_content);
}

char *expansion_d_quo(char *content, int *i, char *new_content, t_shell *shell)//shell
{
	(*i)++;
	while (content[*i] && content[*i] != '"')
	{
		if (content[*i] == '$')
			new_content = expansion_dollar(content, i, new_content, shell);
		if (!content[*i] || content[*i] == '"')
			break ;
		if (content[*i] != '$')
		{	
			new_content = ft_strjoin_char(new_content, content[*i]);
			(*i)++;
		}
	}
	return (new_content);
}

char *expansion_s_quo(char *content, int *i, char *new_content)
{
	(*i)++;
	while (content[*i] && content[*i] != '\'')
	{
		new_content = ft_strjoin_char(new_content, content[*i]);
		(*i)++;
	}
	return (new_content);
}

char	*expansion_check(char *content, t_shell *shell)
{
	char	*new_content;
	int		i;

	i = 0;
	new_content = ft_strdup("\0");
		// protect this
	if (content == NULL)
		return NULL;
	while(content[i])
	{
		if (content[i] == '$')
			new_content = expansion_dollar(content, &i, new_content, shell);
		else if (content[i] == '"')
			new_content = expansion_d_quo(content, &i, new_content, shell);
		else if (content[i] == '\'')
			new_content = expansion_s_quo(content, &i, new_content);
		if (content[i] != '$' && content[i] != '"' && content[i] != '\'')
			new_content = ft_strjoin_char(new_content, content[i]);
		if (!content[i])
			break ;
		if (content[i] != '$')
			i++;
	}
	free(content);
	return (new_content);
}

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

t_table	expandor(t_table table, t_shell *shell)//shell
{
	if (arg_expand(&(table.args), shell) == false)
	{
		table.args[0] = NULL;
		return (table);
	}
	if (redir_expand(table.in, shell) == false)
	{	
		table.args[0] = NULL;
		return (table);
	}
	if (redir_expand(table.out, shell) == false)
	{
		table.args[0] = NULL;
		return (table);
	}
	if (redir_expand(table.append, shell) == false)
	{	
		table.args[0] = NULL;
		return (table);
	}
	if (check_in_expandor(table) == false)
	{	
		table.args[0] = NULL;
		return (table);
	}
	// printf("after expansion\n");
	//print_tables(&table);
	return (table);
}

// typedef struct s_tokens
// {
// 	t_token_type	type;
// 	char			*content;
// 	struct s_tokens	*next;
// }	t_tokens;