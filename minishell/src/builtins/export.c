#include "minishell.h"
// IN PROGRESS, MUST DO FULL QUOTE HANDLING FIRST!!!
/* int		s_quo_count(char *str)
{
	while (*str)
		if (*str == '\'')


}




char *remove_quotes(char *str)
{
	char 	*new_str;
	int		i;
	int		s_quote_count;
	int		d_quote_count;
	
	i = 0;
	s_quote_count = 0;
	d_quote_count = 0;
	while (str[i])
		if (str[i] == '\'' || str[] )
	while (str[i])
	{
		if (str[i] == '\'')
	}

} */

void	ft_export(t_tokens *tokens, t_shell *shell)
{
	char	*var;

	if (tokens->next)
		tokens = tokens->next;
	else
		return ;
	while (tokens->type == STRING)
	{
		//check var!
		var = remove_quotes(tokens->content);
		add_env(shell->env, var);
		tokens = tokens->next;
	}

}