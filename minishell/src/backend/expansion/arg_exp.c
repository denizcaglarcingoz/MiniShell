#include "minishell.h"


char	**add_word_split(char **content, char **exp, int non_expanded, t_shell *shell)
{
	int		content_len;
	int		exp_len;
	char	**joined;

	if (exp == NULL)
		return (content);
	if (content && content[0][0] == '\0' && content[1] == NULL)
		return (exp);
	content_len = 0;
	while (content[content_len] != NULL)
		content_len++;
	content_len--;
	exp_len = 0;
	while (exp[exp_len] != NULL)
		exp_len++;
	joined = (char **)malloc(sizeof(char *) * (content_len + exp_len + 1));
	if (joined == NULL)
	{
		free_d_str(content);
		free_d_str(exp);
		free_all(shell, "Malloc Error\n", 127);
	}
	content_len = 0;
	int k = 0;
	while (k < non_expanded && content[k] != NULL)
	{
		joined[k] = ft_strdup(content[k]);
		k++;
	}
	exp_len = 0;
	while (exp[exp_len] != NULL)
	{
		joined[k] = ft_strdup(exp[exp_len]);
		k++;
		exp_len++;
	}
	non_expanded++;
	while (content[non_expanded] != NULL)
	{
		joined[k] = ft_strdup(content[non_expanded]);
		k++;
		non_expanded++;
	}
	joined[k] = NULL;
	// int i = 0;
	// while (joined[i] != NULL)
	// {
	// 	printf("joined[%d]: |%s|\n", i, joined[i]);
	// 	i++;
	// }
	return (joined);
}

bool arg_expand(char ***ref_content, t_shell *shell)
{
	int		i;
	int		j;
	char	**content;
	char	**exp;

	i = 0;
	j = 0;
	content = *ref_content;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			if (j > 0)
				free_d_str(content);
			printf("minishell: syntax error\n");
			return (false);
		}
		if (str_is_alfa_num(content[i]) == false)
		{
			exp = exp_check(content[i], shell);
			int k = 0;
			k = 0;
			content = add_word_split(content, exp, i, shell);
			int exp_len = 0;
			while (exp[exp_len] != NULL)
			{
				free(exp[exp_len]);
				exp_len++;
			}
			free(exp);
			i = i + exp_len - 1;
			j++;
		}
		i++;
	}
	int  k = 0;
	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
			k++;
		i++;
	}
	if (k == 0)
	{	
		*ref_content = content;
		return (true);
	}
	char **new_content = (char **)malloc(sizeof(char *) * (k + 1));
	if (new_content == NULL)
	{
		perror("malloc");
		return (false);
	}
	new_content[k] = NULL;
	i = 0;
	k = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
		{
			new_content[k] = ft_strdup(content[i]);
			k++;
		}
		i++;
	}
	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
	*ref_content = new_content;
	return (true);
}
