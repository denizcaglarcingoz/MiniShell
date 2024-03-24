#include "../minishell.h"

//SUPER SECRET CODE TO KEEP DENIZ FROM HARVESTING MY MIND-FRUITS.
/**todo**/
//Seems mostly good, further testing to be sure... 
//use quote handling for other places in minishell as well.
char	*handle_env_var_helper(char *token_str, char *path, char *path_start)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*token_str) || *token_str == '_')
	{
		len++;
		token_str++;
	}
	path = ft_substr(path_start, 0, len);
	//protect
	if (getenv(path))
		ft_putstr_fd(getenv(path), 1);
	free(path);
	return (token_str);
}

char	*handle_env_var(char *token_str)
{
	char	*path;
	char	*path_start;

	path = NULL;
	if (*token_str == '$' && *(token_str + 1) && *(token_str + 1) != '\"')
	{
		token_str++;
		path_start = token_str;
		token_str = handle_env_var_helper(token_str, path, path_start);
	}
	else
	{
		write(1, token_str, 1);
		if (token_str + 1)
			token_str++;
	}
	return (token_str);
}

char	*handle_quotes(char *token_str, int d_quote_count, int s_quote_count)
{
	while (*token_str && (*token_str == '\"' || *token_str == '\''))
	{
		if (*token_str == '\"' && d_quote_count % 2 == 0)
		{
			token_str++;
			while (*token_str != '\"')
				token_str = handle_env_var(token_str);
			token_str++;
		}
		else if (*token_str == '\'' && s_quote_count % 2 == 0)
		{
			token_str++;
			while (*token_str != '\'')
			{
				write(1, token_str, 1);
				token_str++;
			}
			token_str++;
		}
		else
			break ;
	}
	return (token_str);
}

static void	parse_and_print(char *token_str)
{
	int		d_quote_count;
	int		s_quote_count;
	char	*start;

	start = token_str;
	d_quote_count = 0;
	s_quote_count = 0;
	while (*token_str)
	{
		if (*token_str == '\"')
			d_quote_count++;
		else if (*token_str == '\'')
			s_quote_count++;
		if (*token_str != '\0')
			token_str++;
	}
	token_str = start;
	while (*token_str)
	{
		token_str = handle_quotes(token_str, d_quote_count, s_quote_count);
		write(1, token_str, 1);
		if (*token_str != '\0')
			token_str++;
	}
}

void	ft_echo(t_tokens **tokens)
{
	bool	flag;

	flag = false;
	if ((*tokens)->next)
	{
		if (!ft_strcmp((*tokens)->next->content, "-n"))
		{
			flag = true;
			*tokens = (*tokens)->next;
		}
		*tokens = (*tokens)->next;
		while ((*tokens)->next)
		{
			parse_and_print((*tokens)->content);
			write(1, " ", 1);
			*tokens = (*tokens)->next;
		}
		parse_and_print((*tokens)->content);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
