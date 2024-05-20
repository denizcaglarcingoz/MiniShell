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

//ft_num_strcmp compares the numeric strings to check the bounds

static int	ft_cmplen(char *n1, char *n2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(n1);
	len2 = ft_strlen(n2);
	if (len1 != len2)
	{
		if (len1 < len2)
			return (-1);
		else
			return (1);
	}
	return (ft_strcmp(n1, n2));
}

int	ft_num_strcmp(char *n1, char *n2)
{
	if (*n1 == '-' && *n2 != '-')
		return (-1);
	if (*n1 != '-' && *n2 == '-')
		return (1);
	if (*n1 == '-' && *n2 == '-')
		return (-ft_num_strcmp(n1 + 1, n2 + 1));
	return (ft_cmplen(n1, n2));
}
