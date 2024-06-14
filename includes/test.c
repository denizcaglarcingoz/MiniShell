#include "minishell.h"


int	main(int ac, char **av)
{

	char *new_content;

	new_content = (char*)malloc(sizeof(char) * 3);
	new_content[0] = '\0';
	new_content[1] = 'a';
	new_content[2] = '\0';

	if (new_content[0] == '\0')
	{
		write(1, "1", 1);
		write(1, &(new_content[0]), 1);
		write(1, "1\n", 2);
		if (new_content[1] != '\0')
		{
			write(1, "2", 1);
			write(1, &(new_content[1]), 1);
			write(1, "2\n", 2);
			if (new_content[2] == '\0')
			{
				write(1, "3", 1);
				write(1, &(new_content[2]), 1);
				write(1, "3\n", 2);
			}
		}
	}
	


}