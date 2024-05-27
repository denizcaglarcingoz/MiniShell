#include "minishell.h"

void	new_content_dquo(char ***new_content, char **content, \
int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = exp_d_quo(*content, i, \
	(*new_content)[j - 1], shell);//pro?
}

void	new_content_squo(char ***new_content, char **content, int *i)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = exp_s_quo(*content, i, (*new_content)[j - 1]);//pro?
}

void	new_content_alt(char ***new_content, char **content, int *i)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = ft_strjoin_char((*new_content)[j - 1], \
	(*content)[*i]);//pro
	(*i)++;
}

char	**exp_check(char *content, t_shell *shell)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = (char **)malloc(sizeof(char *) * 2);//protect
	new_content[0] = ft_strdup("");//protect
	new_content[1] = NULL;
	if (content == NULL)
		return (NULL);
	while (content[i])
	{
		if (content[i] == '$')
			new_content = exp_dollar(content, &i, new_content, shell);
		else if (content[i] == '"')
			new_content_dquo(&new_content, &content, &i, shell);
		else if (content[i] == '\'')
			new_content_squo(&new_content, &content, &i);
		if (content[i] != '\0' && content[i] != '$' && content[i] \
		!= '"' && content[i] != '\'')
			new_content_alt(&new_content, &content, &i);
		if (!content[i])
			break ;
	}
	return (new_content);
}
