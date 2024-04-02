#include "minishell.h"
//working on way to handle quotes for any str and return correct str...

/* #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"
#include "ansi_colors.h" */

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

char	*handle_env_var_helper_1(char *str, char *path, char *path_start, size_t *str_len)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);
	//protect
	if (getenv(path))
	{
		ft_putstr_color_fd(1, getenv(path), GREEN);
		(*str_len) += ft_strlen(getenv(path));//add len use ft_strlen
	}
	free(path);
	return (str);
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
		write(1, str, 1);///testing
		(*str_len)++;//count length for malloc
		if (*(str + 1))// *
			str++;
	}
	return (str);
}

char	*handle_quotes_1(char *str, int d_quote_count, int s_quote_count, size_t *str_len)
{
	while (*str && (*str == '\"' || *str == '\''))
	{
		if (*str == '\"' && d_quote_count % 2 == 0)
		{
			str++;
			//(*str_len)++;//
			while (*str != '\"' && *str)
				str = handle_env_var_1(str, str_len);
			if (*str)
			{
				str++;
			//	(*str_len)++;//
			}
		}
		else if (*str == '\'' && s_quote_count % 2 == 0)
		{
			str++;
			while (*str != '\'' && *str)
			{
				write(1, str, 1);///testing
				(*str_len)++;
				str++;
			}
			
			if (*str)
			str++;
		}
		else
			break ;
	}
	return (str);
}
char	*handle_all_quotes(char *str, size_t *str_len)
{
	int	s_quotes;
	int	d_quotes;
	//size_t str_len;//count len first

	//str_len = 0;//count
	s_quotes = count_s_quotes(str);
	d_quotes = count_d_quotes(str);
	while (*str)
	{
		if (*str == '$')//for handling if the first is $
			str = handle_env_var_1(str, str_len);
		else
			str = handle_quotes_1(str, s_quotes, d_quotes, str_len);	
		write(1, str, 1);///testing
		(*str_len)++;
		if (*str)
			str++;
	}

	return (str);
}
//cc handle_quotes.c -I./libft -L./libft -lft

//testing ---------------------
int main(void)
{
	 char input[] = "$HOME is 'here'";
    size_t str_len = 0;
    handle_all_quotes(input, &str_len);
   // printf("|");
	printf("\n");
	printf("Length: %zu\n", str_len);
	printf("real len: %zu\n", ft_strlen("/home/dopeassprogramming is where the |heart is|"));

	return (0);
}
/* char	*handle_env_var_helper(char *str, char *path, char *path_start, int *p_flag)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);
	//protect
	if (getenv(path))
		*p_flag = ft_putstr_color_fd(1, getenv(path), GREEN);
	free(path);
	return (str);
}

char	*handle_env_var(char *str, int *p_flag)
{
	char	*path;
	char	*path_start;

	path = NULL;
	if (*str == '$' && *(str + 1) && *(str + 1) != '\"')
	{
		str++;
		path_start = str;
		str = handle_env_var_helper(str, path, path_start, p_flag);
	}
	else
	{
		write(1, str, 1);
		if (str + 1)
			str++;
	}
	return (str);
}

char	*handle_quotes(char *str, int d_quote_count, int s_quote_count, int *p_flag)
{
	while (*str && (*str == '\"' || *str == '\''))
	{
		if (*str == '\"' && d_quote_count % 2 == 0)
		{
			str++;
			while (*str != '\"')
				str = handle_env_var(str, p_flag);
			str++;
		}
		else if (*str == '\'' && s_quote_count % 2 == 0)
		{
			str++;
			while (*str != '\'')
			{
				write(1, str, 1);
				str++;
			}
			str++;
		}
		else
			break ;
	}
	return (str);
}

static void	parse_and_print(char *str, int *p_flag)
{
	int		d_quote_count;
	int		s_quote_count;
	char	*start;

	start = str;
	d_quote_count = 0;
	s_quote_count = 0;
	while (*str)
	{
		if (*str == '\"')
			d_quote_count++;
		else if (*str == '\'')
			s_quote_count++;
		if (*str != '\0')//test without this... just replace all with quote count functions...
			str++;
	}
	str = start;
	while (*str)
	{
		if (*str == '$')
		str = handle_env_var(str, p_flag);
		str = handle_quotes(str, d_quote_count, s_quote_count, p_flag);
		write(1, str, 1);
		if (*str != '\0')
			str++;
	}
}
 */


























