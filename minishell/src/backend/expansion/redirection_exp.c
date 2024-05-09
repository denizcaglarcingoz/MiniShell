#include "minishell.h"

char	**word_split(char *new_exp, t_shell *shell)
{
	char	**new_d_exp;

	new_d_exp = ft_split(new_exp, ' ');
	if (new_d_exp == 0)
		free_all(shell, "Malloc Error\n", 127); 
	return (new_d_exp);
}

char	**exps(char *exp, t_shell *shell)
{
	char	**new_d_exp;
	char	*new_exp;
	char	*temp;
	int		i;

	if (exp == NULL || exp[0] == '\0')
		return (NULL);
	i = 0;
	temp = exp;
	exp = ft_strjoin_char(exp, '=');
	//free(temp);
	new_exp = ft_strdup("");
	new_d_exp = NULL;
	while (shell->env[i] && ft_strlen(exp) > 1)
	{
		if (ft_strncmp(exp, shell->env[i], ft_strlen(exp)) == 0)
		{
			temp = new_exp;
			new_exp = ft_strjoin(new_exp, shell->env[i] + ft_strlen(exp));
			free(temp);
			if (new_exp == NULL)
				free_all(shell, "Malloc Error\n", 127);
			new_d_exp = word_split(new_exp, shell);
		}
		i++;
	}
	return (new_d_exp);
}

char	**add_new_content(char **new_content, char **d_exp, t_shell *shell)
{
	int		new_content_len;
	int		d_exp_len;
	char	**joined;

	if (d_exp == NULL)
		return (new_content);
	if (new_content && new_content[0][0] == '\0' && new_content[1] == NULL)
		return (d_exp);
	new_content_len = 0;
	while (new_content[new_content_len] != NULL)
		new_content_len++;
	new_content[new_content_len - 1] = ft_strjoin(new_content[new_content_len - 1], d_exp[0]);
	d_exp_len = 0;
	while (d_exp[d_exp_len] != NULL)
		d_exp_len++;
	joined = (char **)malloc(sizeof(char *) * (new_content_len + d_exp_len));
	if (joined == NULL)
	{
		free_d_str(new_content);
		free_d_str(d_exp);
		free_all(shell, "Malloc Error\n", 127);
	}
	new_content_len = 0;
	while (new_content[new_content_len] != NULL)
	{
		joined[new_content_len] = ft_strdup(new_content[new_content_len]);
		new_content_len++;
	}
	d_exp_len = 0;
	while (d_exp[d_exp_len + 1] != NULL)
	{
		joined[new_content_len] = ft_strdup(d_exp[d_exp_len + 1]);
		new_content_len++;
		d_exp_len++;
	}
	joined[new_content_len - 1] = NULL;
	free_d_str(new_content);
	free_d_str(d_exp);
	return (joined);
}

char	**exp_dollar(char *content, int *i, char **new_content, t_shell *shell)//shell
{
	char	*to_exp;
	char	**d_exp;

	to_exp = ft_strdup("");
	(*i)++;
	while (content[*i] && is_alfa_num(content[*i]) == true)
	{
		to_exp = ft_strjoin_char(to_exp, content[*i]);
		(*i)++;
	}
	d_exp = exps(to_exp, shell);
	// free(to_exp);
	new_content = add_new_content(new_content, d_exp, shell);
	return (new_content);
}

char	**exp_check(char *content, t_shell *shell)
{
	char	**new_content;
	int		i;
	int		j;

	i = 0;
	new_content = (char **)malloc(sizeof(char *)* 2);
	new_content[0] = ft_strdup("");
	new_content[1] = NULL;
	// protect this  
		
	if (content == NULL)
		return NULL;
	while(content[i])
	{
		if (content[i] == '$')
		{
			new_content = exp_dollar(content, &i, new_content, shell);
		}
		else if (content[i] == '"')
		{
			j = 0;
			while (new_content[j] != NULL)
				j++;
			new_content[j - 1] = exp_d_quo(content, &i, new_content[j- 1], shell);
		}
		else if (content[i] == '\'')
		{	
			j = 0;
			while (new_content[j] != NULL)
				j++;
			new_content[j - 1] = exp_s_quo(content, &i, new_content[j - 1]);
		}
		if (content[i] != '\0' && content[i] != '$' && content[i] != '"' && content[i] != '\'')
		{
			j = 0;
			while (new_content[j] != NULL)
				j++;
			new_content[j- 1] = ft_strjoin_char(new_content[j - 1], content[i]);
			i++;
		}
		if (!content[i])
			break ;
	}
	//free(content);
	return (new_content);
}

bool	redir_expand(char **content, t_shell *shell)//shell
{
	int		i;
	char	**exp;

	i = 0;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
		if (str_is_alfa_num(content[i]) == false)
		{
			exp = exp_check(content[i], shell);
			if (exp[1] != 0 || (exp[0][0] == '\0' && exp[1] == NULL))
			{
				printf("bash: %s: ambiguous redirect\n", content[i]);
				return (false);
			}
			content[i] = exp[0];
		}
		i++;
	}
	return (true);
}
