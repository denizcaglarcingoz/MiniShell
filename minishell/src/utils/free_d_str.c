#include "minishell.h"

void	free_d_str(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;	
	}
	free(str);
}