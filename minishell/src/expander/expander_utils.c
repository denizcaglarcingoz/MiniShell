#include "minishell.h"


char	*get_exit_status_len(char *str, size_t *total_len, t_shell *shell)//get from shellstruct in case of calling added var...
{
	char *exit_stat;
	size_t	exit_len;

	exit_stat = ft_itoa(shell->exit_status);
	exit_len = ft_strlen(exit_stat);
	
	ft_putstr_color_fd(1, exit_stat, BLUE);//testing..
	free(exit_stat);
	*total_len += exit_len;
	str++; 
	return (str);
}

char	*get_var_len(char *str, size_t *total_len, t_shell *shell)
{
	size_t	len;
	char	*path;
	char	*path_start;

	//parse single dollar..
	path_start = str;
	
	int exit_s = shell->exit_status;//for unused
	exit_s++;//
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);
	//protect
	if (ft_getenv(path, shell->env))
	{
		ft_putstr_color_fd(1, getenv(path), GREEN);//testing	
		(*total_len) += ft_strlen(getenv(path)) - 1; //look at why it is 1 too long..
	}
	free(path);
	return (str);
}

size_t	get_expanded_len(char *str, t_shell *shell)//pass in shell struct for exit size and env...make get env for ours
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
		if (*str == '$' && *(str + 1) == '?' && !in_s_quote)
		{
			str = get_exit_status_len(str + 1, &total_len, shell);//todo
		}
		else if (*str == '$' && !in_s_quote)
			str = get_var_len(str + 1, &total_len, shell);
		else
		{	
			write(1, str, 1);///testing
			str++;
		}
		total_len++;
	}
	return (total_len);//then malloc and build...
}