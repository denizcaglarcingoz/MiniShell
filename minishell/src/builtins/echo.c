#include "minishell.h"
//test print
/* char **print_cmd(char **cmd)
{
	char **temp = cmd;
	while (temp)
	{
		ft_putstr_fd(*temp, 1);
		ft_putchar_fd('\n', 1);
		temp++;
	}
	return cmd;
} */
	//full_cmd = print_cmd(full_cmd);

int	ft_echo(char **full_cmd)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	if (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (full_cmd[i] && *(full_cmd[i]))
	{
		ft_putstr_fd(full_cmd[i], 1);
		i++;
		if (full_cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
