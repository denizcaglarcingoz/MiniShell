#include "minishell.h"

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
			content = split_join(content, exp, i, shell);
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
		if (ft_strlen(content[i]) == 0)
			k++;
		i++;
	}
	if (k == 0)
	{	
		*ref_content = content;
		return (true);
	}
	k = 0;
	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
			k++;
		i++;
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
