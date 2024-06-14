#include "minishell.h"

void	hdoc_new_content_alt(char ***new_content, char **content, int *i)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = ft_strjoin_char((*new_content)[j - 1], \
	(*content)[*i]);//pro
	(*i)++;
}

char	*hdoc_exp_d_quo(char *cntnt, int *i, char *new_cntnt, t_shell *shell)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '"')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			free_all(shell, "new_cntnt malloc", 127);
		if (!cntnt[*i] || cntnt[*i] == '"')
			break ;
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '"')
		(*i)++;
	return (new_cntnt);
}

char	*hdoc_exp_s_quo(char *cntnt, int *i, char *new_cntnt)
{
	(*i)++;
	while (cntnt[*i] && cntnt[*i] != '\'')
	{
		new_cntnt = ft_strjoin_char(new_cntnt, cntnt[*i]);
		if (new_cntnt == NULL)
			return (NULL);
		(*i)++;
	}
	if (cntnt[*i] && cntnt[*i] == '\'')
		(*i)++;
	return (new_cntnt);
}


void	hdoc_new_content_dquo(char ***new_content, char **content, \
int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = hdoc_exp_d_quo(*content, i, \
	(*new_content)[j - 1], shell);//pro?l
}

void	hdoc_new_content_squo(char ***new_content, char **content, int *i)
{
	int	j;

	j = 0;
	while ((*new_content)[j] != NULL)
		j++;
	(*new_content)[j - 1] = hdoc_exp_s_quo(*content, i, (*new_content)[j - 1]);//pro?
}

void	hdoc_init_new_content(char ***new_content, t_shell *shell)
{
	*new_content = (char **)malloc(sizeof(char *) * 2);
	if (!(*new_content))
		free_all(shell, "new_content malloc", 127);
	(*new_content)[0] = ft_strdup("");
	if (!((*new_content)[0]))
	{
		free(*new_content);
		free_all(shell, "new_content[0]", 127);
	}
	(*new_content)[1] = NULL;
}

char	**hdoc_exp_check(char *content, t_shell *shell)
{
	char	**new_content;
	int		i;

	i = 0;
	new_content = NULL;
	hdoc_init_new_content(&new_content, shell);
	if (content == NULL)
		return (NULL);
	while (content[i])
	{
		if (content[i] == '"')
			hdoc_new_content_dquo(&new_content, &content, &i, shell);
		else if (content[i] == '\'')
			hdoc_new_content_squo(&new_content, &content, &i);
		if (content[i] != '\0' && content[i] \
		!= '"' && content[i] != '\'')
			hdoc_new_content_alt(&new_content, &content, &i);
		if (!content[i])
			break ;
	}
	return (new_content);
}



bool	hdoc_expand(char **content, t_shell *shell)
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
			exp = hdoc_exp_check(content[i], shell);
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