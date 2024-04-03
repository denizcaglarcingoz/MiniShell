#include "minishell.h"

/* 
char	*get_exit_status_len(char *str, size_t *total_len)//get from shellstruct in case of calling added var...
{
	

} */

char	*get_var_len(char *str, size_t *total_len)
{
	size_t	len;
	char	*path;
	char	*path_start;

	//parse single dollar..
	path_start = str;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);
	//protect
	if (getenv(path))//replace with ft_getenv...?
	{
		ft_putstr_color_fd(1, getenv(path), GREEN);//testing	
		(*total_len) += ft_strlen(getenv(path)) - 1; //look at why it is 1 too long..
	}
	free(path);
	return (str);
}

size_t	get_expanded_len(char *str)//pass in shell struct for exit size and env...make get env for ours
{
	bool	in_s_quote;
	bool	in_d_quote;
	size_t	total_len;

	//perform quote count check and return error... init and check function?
	in_s_quote = 0;
	in_d_quote = 0;
	total_len = 0;
	while (*str)
	{
		if (*str == '\"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		if (*str == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		/* if (*str == '$' && *(str + 1) == '?' && !in_s_quote)
		{
			str = get_exit_status_len(str + 1, &total_len);//todo
		} */
		//else if
		if (*str == '$' && !in_s_quote)
			str = get_var_len(str + 1, &total_len);
		else
			str++;
		write(1, str, 1);///testing
		total_len++;
	}
	return (total_len);//then malloc and build...
}
//test-------------------------------
//cc expander.c -I./libft -L./libft -lft
int main(void)
{
	 char input[] = "$HOME_ is 'here'";
    size_t len;
    len = get_expanded_len(input);
    //printf("|");
	printf("\n");
	printf("Length: %zu\n", len);
	printf("real len: %zu\n", ft_strlen("/home/dopeassprogramming is 'here'"));

	return (0);
}