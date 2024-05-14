#include "minishell.h"

void	free_d_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;	
	}
	free(str);
}