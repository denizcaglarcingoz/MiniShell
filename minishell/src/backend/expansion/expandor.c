#include "minishell.h"

char *ft_strjoin_char(char *s1, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}

char	*expand(char *exp)
{
	char	*new_exp;
	int		i;
	extern char **environ;

	i = 0;
	exp = ft_strjoin_char(exp, '=');
	new_exp = ft_strdup("");
	while (environ[i])
	{
		if (ft_strncmp(exp, environ[i], ft_strlen(exp)) == 0)
		{
			new_exp = ft_strjoin(new_exp, environ[i] + ft_strlen(exp));
		}
		i++;
	}
	free(exp);
	return (new_exp);
}

bool is_alfa_num(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

char	*expansion_dollar(char **content, int *i, char *new_content)
{
	char	*exp;

	exp = ft_strdup("\0");
	(*i)++;
	while ((*content)[*i] && is_alfa_num((*content)[*i]) == true)
	{
		exp = ft_strjoin_char(exp, (*content)[*i]);
		(*i)++;
	}
	exp = expand(exp);
	new_content = ft_strjoin(new_content, exp);
	free(exp);
	return (new_content);
}
char *expansion_d_quo(char **content, int *i, char *new_content)
{
	(*i)++;
	while ((*content)[*i] && (*content)[*i] != '"')
	{
		if ((*content)[*i] == '$')
			new_content = expansion_dollar(content, i, new_content);
		if (!(*content)[*i] || (*content)[*i] == '"')
			break ;
		if ((*content)[*i] != '$')
		{	
			new_content = ft_strjoin_char(new_content, (*content)[*i]);
			(*i)++;
		}
	}
	return (new_content);
}

char *expansion_s_quo(char **content, int *i, char *new_content)
{
	(*i)++;
	while ((*content)[*i] && (*content)[*i] != '\'')
	{
		new_content = ft_strjoin_char(new_content, (*content)[*i]);
		(*i)++;
	}
	return (new_content);
}

void	expansion_check(char **content)
{
	char	*new_content;
	int		i;

	i = 0;
	new_content = ft_strdup("\0");
	while((*content)[i])
	{
		if ((*content)[i] == '$')
			new_content = expansion_dollar(content, &i, new_content);
		else if ((*content)[i] == '"')
			new_content = expansion_d_quo(content, &i, new_content);
		else if ((*content)[i] == '\'')
			new_content = expansion_s_quo(content, &i, new_content);
		if ((*content)[i] != '$' && (*content)[i] != '"' && (*content)[i] != '\'')
			new_content = ft_strjoin_char(new_content, (*content)[i]);
		if (!(*content)[i])
			break ;
		i++;
	}
	free(*content);
	*content = new_content;
}

bool content_check(char *content)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
			{	
				if (content[i] == '\'')
					break;
				i++;
			}
			if (!content[i])
				return (false);
		}
		else if (content[i] == '"')
		{
			i++;
			while (content[i] && content[i] != '"')
			{
				if (content[i] == '"')
					break;
				i++;
			}
			if (!content[i])
				return (false);
		}
		i++;
	}
	return (true);
}

t_tokens	*expandor(t_tokens *tokens)
{
	int			i;
	t_tokens	*token_start;

	i = 0;
	token_start = tokens;
	while (tokens)
	{
		if (tokens->type == STRING)
		{	
			if (content_check((tokens->content)) == false)
			{
				printf("minishell: syntax error\n");
				//free_tokens(tokens_start);
				return (NULL);
			}
			expansion_check(&(tokens->content));
		}
		tokens = tokens->next;
	}
	return (token_start);
}

// typedef struct s_tokens
// {
// 	t_token_type	type;
// 	char			*content;
// 	struct s_tokens	*next;
// }	t_tokens;