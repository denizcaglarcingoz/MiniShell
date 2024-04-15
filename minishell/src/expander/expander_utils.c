#include "minishell.h"


char	*handle_exit_stat(char *str, size_t *total_len, t_shell *shell)//get from shellstruct in case of calling added var...
{
	char *exit_stat;
	size_t	exit_len;

	//printf("curr str: %c\n", *(str));
	exit_stat = ft_itoa(shell->exit_status);
	exit_len = ft_strlen(exit_stat);
	
	//ft_putstr_color_fd(1, exit_stat, BLUE);//testing..
	free(exit_stat);
	*total_len += exit_len;
	str++; 
	return (str);
}

char	*handle_var(char *str, size_t *total_len, t_shell *shell)
{
	size_t	len;
	char	*path;
	char	*path_start;

	//parse single dollar..
	path_start = str;
	len = 0;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);
		//protect
	if (ft_getenv(path, shell->env))//must protect against failure, maybe better inside ft_getenv function
		(*total_len) += ft_strlen(ft_getenv(path, shell->env));
	free(path);
	return (str);
}

size_t	get_expanded_len(char *str, t_shell *shell)
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
		if (*str == '$' && *(str + 1) == '?' && !in_s_quote) //handle for if no str + 1;
		{
			str = handle_exit_stat(str + 1, &total_len, shell);
		}
		else if (*str == '$' && !in_s_quote)
			str = handle_var(str + 1, &total_len, shell);
		else
		{	
			total_len++;
			str++;
		}
	}
	return (total_len);
}
			//write(1, str, 1);///testing
	/* printf("here is the current char: %c\n", *str);
	printf("here is the current total: %zu\n", total_len); */
	//printf("no fault yet utils\n");
	//printf("here is the current char: %c\n", *str);
		//ft_putstr_color_fd(1, ft_getenv(path, shell->env), GREEN);//testing	