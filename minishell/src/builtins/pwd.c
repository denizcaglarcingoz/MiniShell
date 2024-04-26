#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_color_fd(1, "current directory: ", MAGENTA);
	ft_putstr_color_fd(1, cwd, CYAN);
	ft_putchar_fd('\n', 1);
	return (0);
}
