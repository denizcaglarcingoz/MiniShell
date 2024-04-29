#include "../../includes/minishell.h"

int	ft_echo(char **full_cmd)
{
	bool	flag;

	flag = false;
	full_cmd++;
	if (*full_cmd && !ft_strcmp(*full_cmd, "-n"))
	{
		flag = true;
		full_cmd++;
	}
	while (*full_cmd && **full_cmd)
	{
		ft_putstr_fd(*full_cmd, 1);
		full_cmd++;
		if(*full_cmd)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}