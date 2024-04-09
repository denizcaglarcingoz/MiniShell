#include "minishell.h"

char	*exp_var(char **exp_curr, char *str, t_shell *shell)
{
	size_t	len;
	char	*path;
	char	*path_start;
	char	*env_var;

	//parse single dollar..
	len = 0;
	path_start = str;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len);//put inside getenv?
	//protect
	env_var = ft_getenv(path, shell->env);
	free(path);
	if (env_var)//must protect against failure, maybe better inside ft_getenv function
	{
		
		while (*env_var)
		{
			**exp_curr = *env_var;
			(*exp_curr)++;
			env_var++;
		}
		//(*exp_curr)++;
		// ft_putstr_color_fd(1, env_var, GREEN);//testing
	}
	//(*total_len)--;
	return (str);
	//printf("no fault yet\n");
}

char	*expander(char *str, t_shell *shell)//pass in shell struct for exit size and env
{
	bool	in_s_quote;
	bool	in_d_quote;
	char	*expanded;
	char	*exp_curr;
	//char	*str_start; put back for malloced; out for test...

	in_s_quote = 0;
	in_d_quote = 0;
	expanded = (char *)malloc((get_expanded_len(str, shell) + 1) * sizeof(char));//protect
	exp_curr = expanded;
	//str_start = str;
	while (*str)
	{
		if (*str == '\"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		if (*str == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		/* if (*str == '$' && *(str + 1) == '?' && !in_s_quote)
		{
			str = exp_exit_stat(str + 1, shell);
		} */
		else if (*str == '$' && !in_s_quote)
			str = exp_var(&exp_curr, str + 1, shell);
		else
		{	
			*exp_curr = *str;
			exp_curr++;
			str++;
		}
	}
	//exp_curr[] = '\0';
	//printf("no fault yet\n");
	//free(str_start);
	return (expanded);//then malloc and build...
}