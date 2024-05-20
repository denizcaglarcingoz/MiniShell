#include "minishell.h"

char	*quo_exp(char *exp, t_shell *shell)
{
	char	*new_exp;
	int		i;

	i = 0;
	exp = ft_strjoin_char(exp, '=');
	new_exp = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(exp, shell->env[i], ft_strlen(exp)) == 0)
		{
			new_exp = ft_strjoin(new_exp, shell->env[i] + ft_strlen(exp));
		}
		i++;
	}
	free(exp);
	return (new_exp);
}

char	*quo_exp_dollar(char *content, int *i, char *new_content, \
t_shell *shell)
{
	char	*exp;
	char	*temp;

	temp = new_content;
	(*i)++;
	if (content[*i] == '?')
	{
		(*i)++;
		exp = quo_dollar_question(shell);
		new_content = ft_strjoin(new_content, exp);
		free(temp);
		free(exp);
		return (new_content);
	}
	exp = ft_strdup("");
	while (content[*i] && is_alfa_num(content[*i]) == true)
	{
		exp = ft_strjoin_char(exp, content[*i]);
		(*i)++;
	}
	exp = quo_exp(exp, shell);
	new_content = ft_strjoin(new_content, exp);
	free(temp);
	free(exp);
	return (new_content);
}

char	*exp_d_quo(char *content, int *i, char *new_content, t_shell *shell)
{
	(*i)++;
	while (content[*i] && content[*i] != '"')
	{
		if (content[*i] == '$')
			new_content = quo_exp_dollar(content, i, new_content, shell);
		if (!content[*i] || content[*i] == '"')
			break ;
		if (content[*i] != '$')
		{
			new_content = ft_strjoin_char(new_content, content[*i]);
			(*i)++;
		}
	}
	if (content[*i] && content[*i] == '"')
		(*i)++;
	return (new_content);
}

char	*exp_s_quo(char *content, int *i, char *new_content)
{
	(*i)++;
	while (content[*i] && content[*i] != '\'')
	{
		new_content = ft_strjoin_char(new_content, content[*i]);
		(*i)++;
	}
	if (content[*i] && content[*i] == '\'')
		(*i)++;
	return (new_content);
}
