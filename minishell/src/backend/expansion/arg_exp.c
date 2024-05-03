#include "minishell.h"

bool arg_expand(char ***ref_content, t_shell *shell)
{
	int		i;
	char	**content;
	i = 0;
	content = *ref_content;
	while (content[i])
	{
		if (content_check(content[i]) == false)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
		content[i] = expansion_check(content[i], shell);
		i++;
	}
	i = 0;
	int k = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
			k++;
		i++;
	}
	if (k == 0)
		return (true);
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