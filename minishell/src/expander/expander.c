#include "minishell.h"

static char *handle_exit_s(char **exp_curr, char *str, t_shell *shell)
{
	char *exit_stat;
	size_t	exit_len;

	exit_stat = ft_itoa(shell->exit_status);
	exit_len = ft_strlen(exit_stat);
	while (*exit_stat)
	{
	**exp_curr = *exit_stat;
	(*exp_curr)++;
	exit_stat++;
	}
	free(exit_stat - exit_len);
	str++; 
	return (str);
}

static char *handle_env_var(char **exp_curr, char *str, t_shell *shell)
{
	size_t len;
	char *path;
	char *path_start;
	char *env_var;
	// parse single dollar..
	len = 0;
	path_start = str;
	while (ft_isalnum(*str) || *str == '_')
	{
		len++;
		str++;
	}
	path = ft_substr(path_start, 0, len); // put inside getenv?
	// protect
	env_var = ft_getenv(path, shell->env);
	free(path);
	if (env_var) // must protect against failure, maybe better inside ft_getenv function
	{
		while (*env_var)
		{
			**exp_curr = *env_var;
			(*exp_curr)++;
			env_var++;
		}
	}
	return (str);
}

char *expander(char *str, t_shell *shell) // pass in shell struct for exit size and env
{
	bool	in_s_quote;
	bool	in_d_quote;
	char	*expanded;
	char	*exp_curr;
	char	*str_start;

	in_s_quote = 0;
	in_d_quote = 0;
	expanded = (char *)malloc((get_expanded_len(str, shell) + 1) * sizeof(char)); // protect
	exp_curr = expanded;
	str_start = str;
	while (*str)
	{
		/* if (*str == '\"' && !in_s_quote)
		{
			in_d_quote = !in_d_quote;
			str++;
			continue;
		}
		if (*str == '\'' && !in_d_quote)
		{
			in_s_quote = !in_s_quote;
			str++;
			continue;
		} */
		if (*str == '\"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		if (*str == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		if (*str == '$' && *(str + 1) == '?' && !in_s_quote)
			str = handle_exit_s(&exp_curr, str + 1, shell);
		else if (*str == '$' && !in_s_quote)
			str = handle_env_var(&exp_curr, str + 1, shell);//handle for just dollar
		else
		{
			*exp_curr = *str;
			exp_curr++;
			str++;
		}
	}
	*exp_curr = '\0';
	free(str_start);
	return (expanded);
}
	//printf("no fault yet\n");