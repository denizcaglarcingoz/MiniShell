#include "minishell.h"
//working on way to handle quotes for any str and return correct str...
char	*handle_env_var_helper_1(char *token_str, char *path, char *path_start, size_t *str_len)
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
		str_len += ft_strlen(getenv(path));//add len
	free(path);
	return (token_str);
}

char	*handle_env_var_1(char *str, size_t *str_len)
{
	char	*path;
	char	*path_start;

	path = NULL;
	if (*str == '$' && *(str + 1) && *(str + 1) != '\"')
	{
		str++;
		path_start = str;
		str = handle_env_var_helper_1(str, path, path_start, str_len);
	}
	else
	{
		str_len++;//count length for malloc?
		if (str + 1)
			str++;
	}
	return (str);
}

char	*handle_quotes_1(char *token_str, int d_quote_count, int s_quote_count, size_t *str_len)
{
	while (*token_str && (*token_str == '\"' || *token_str == '\''))
	{
		if (*token_str == '\"' && d_quote_count % 2 == 0)
		{
			token_str++;
			while (*token_str != '\"')
				token_str = handle_env_var_1(token_str, str_len);
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
char	*handle_all_quotes(char *str)
{
	int	s_quotes;
	int	d_quotes;
	size_t str_len;//count len first

	str_len = 0;//count
	s_quotes = count_s_quotes(str);
	d_quotes = count_d_quotes(str);
	while (*str)
	{
		if(*str == '$')//for handling if the first is $
			str = handle_env_var_1(str, &str_len);
		str = handle_quotes_1(str, s_quotes, d_quotes, &str_len);	
	}
	return (str);
}
//testing ---------------------
int main(void)
{


	return (0);
}
/* static void	parse_and_print(char *token_str, int *p_flag)
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
		if (*token_str == '$')
		token_str = handle_env_var_1(token_str, p_flag);
		token_str = handle_quotes_1(token_str, d_quote_count, s_quote_count, p_flag);
		write(1, token_str, 1);
		if (*token_str != '\0')
			token_str++;
	}
} */

int		count_s_quotes(char *str)//count s
{
	int		s_quotes;

	s_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
			s_quotes++;
		str++;
	}
	return (s_quotes);
}

int		count_d_quotes(char *str)//count d
{
	int		s_quotes;

	s_quotes = 0;
	while (*str)
	{
		if (*str == '\"')
			s_quotes++;
		str++;
	}
	return (s_quotes);
}




























