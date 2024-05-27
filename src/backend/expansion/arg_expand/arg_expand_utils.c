#include "minishell.h"

void	len_loop(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) == 0)
			(*k)++;
		i++;
	}
}

void	len_loop_2(char **content, int *k)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_strlen(content[i]) != 0)
			(*k)++;
		i++;
	}
}

void	free_content(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
	content = NULL;
}
