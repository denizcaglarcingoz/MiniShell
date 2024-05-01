#include "minishell.h"

void	cd_not_found(char **full_cmd)
{
	ft_putstr_color_fd(2, "minishell: cd: ", RED);
	ft_putstr_color_fd(2, full_cmd[1], RED);
	ft_putstr_color_fd(2, " No such file or directory\n", RED);
}

int	invalid_id(char *id)
{
	ft_putstr_color_fd(2, "minishell: export: '", RED);
	ft_putstr_color_fd(2, id, RED);
	ft_putstr_color_fd(2, "': not a valid identifier\n", RED);
	return (1);
}
