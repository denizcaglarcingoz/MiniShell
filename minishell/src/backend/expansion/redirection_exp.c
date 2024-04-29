#include "minishell.h"

bool	redir_expand(char **content)
{
	int		i;
	char	*temp;

	i = 0;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
		temp = ft_strdup(content[i]);
		content[i] = expansion_check(content[i]);
		if (ft_strlen(content[i]) == 0)
		{
			printf("bash: %s: ambiguous redirect\n", temp);
			free(temp);
			return (false);
		}
		free(temp);
		i++;
	}
	return (true);
}