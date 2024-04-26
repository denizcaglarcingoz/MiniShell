#include "minishell.h"
//test print
/* char **print_cmd(char **cmd)
{
	char **temp = cmd;
	while (temp)
	{
		ft_putstr_fd(*temp, 1);
		ft_putchar_fd('\n', 1);
		temp++;
	}
	return cmd;
} */
	//full_cmd = print_cmd(full_cmd);

int	ft_echo(char **full_cmd)
{
	bool	flag;
	
	flag = false;
	full_cmd++;
	if (*full_cmd && !ft_strcmp(*full_cmd, "-n"))
	{
		flag = true;
		full_cmd++;
	}
	while (*full_cmd && **full_cmd)
	{
		ft_putstr_fd(*full_cmd, 1);
		full_cmd++;
		if(*full_cmd)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

//Seems mostly good, further testing to be sure... 
//use quote handling for other places in minishell as well., some weird behaviours of '$' in bash to look into...
/* char	*handle_env_var_helper(char *token_str, char *path, char *path_start, int *p_flag)
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
		*p_flag = ft_putstr_color_fd(1, getenv(path), GREEN);
	free(path);
	return (token_str);
}

char	*handle_env_var(char *token_str, int *p_flag)
{
	char	*path;
	char	*path_start;

	path = NULL;
	if (*token_str == '$' && *(token_str + 1) && *(token_str + 1) != '\"')
	{
		token_str++;
		path_start = token_str;
		token_str = handle_env_var_helper(token_str, path, path_start, p_flag);
	}
	else
	{
		write(1, token_str, 1);
		if (token_str + 1)
			token_str++;
	}
	return (token_str);
}

char	*handle_quotes(char *token_str, int d_quote_count, int s_quote_count, int *p_flag)
{
	while (*token_str && (*token_str == '\"' || *token_str == '\''))
	{
		if (*token_str == '\"' && d_quote_count % 2 == 0)
		{
			token_str++;
			while (*token_str != '\"')
				token_str = handle_env_var(token_str, p_flag);
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

static void	parse_and_print(char *token_str, int *p_flag)
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
		if (*token_str != '\0')//test without this... just replace all with quote count functions...
			token_str++;
	}
	token_str = start;
	while (*token_str)
	{
		if (*token_str == '$')
		token_str = handle_env_var(token_str, p_flag);
		token_str = handle_quotes(token_str, d_quote_count, s_quote_count, p_flag);
		write(1, token_str, 1);
		if (*token_str != '\0')
			token_str++;
	}
}

void	ft_echo(t_tokens *tokens)
{
	bool	flag;
	int		p_flag;

	p_flag = 0;
	flag = false;
	if (tokens->next)
	{
		if (!ft_strcmp(tokens->next->content, "-n"))
		{
			flag = true;
			tokens = tokens->next;
		}
		tokens = tokens->next;
		while (tokens->next)// handle so stops for operator types.... 
		{
			parse_and_print(tokens->content, &p_flag);
			if (!(*(tokens->content) == '$' && !p_flag))/// this is to fix DONT PRINT SPACE WHEN TOKEN PRINTS NOTHING.. AS IN BAD EVNVAR
			write(1, " ", 1);
			tokens = tokens->next;
		}
		parse_and_print(tokens->content, &p_flag);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
 */