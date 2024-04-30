#include "minishell.h"

//double free occurs sometimes, why
int	has_equal(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	check_valid_id(char *s)
{
	int	i;
	i = 0;	
	if (ft_isdigit(s[i]) || !(s[i] == '_' || ft_isalpha(s[i])))
		return (1);
	while (s[++i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i])) && !(s[i] == '_'))
			return (1);
	}
	return (0);
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	if (env == NULL || !env[0])
	{
		ft_putstr_color_fd(1, "Empty Exported Variable List\n", BOLD_BLUE);
		return ;
	}
	while (env[++i] != NULL)
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j] != '=')
			ft_putchar_fd(env[i][j], 1);
		ft_putchar_fd(env[i][j], 1);
		ft_putstr_fd("\"", 1);
		while (env[i][++j])
			ft_putchar_fd(env[i][j], 1);
		ft_putstr_fd("\"\n", 1);
	}
}

int	invalid_id(char *id)
{
	ft_putstr_color_fd(2, "minishell: export: '", RED);
	ft_putstr_color_fd(2, id, RED);
	ft_putstr_color_fd(2, "': not a valid identifier\n", RED);
	return (1);
}

int	ft_export(char **full_cmd, t_shell *shell)
{
	int		i;
	int		status;

	status = 0;
	if (!(*(full_cmd + 1)))
		print_export(shell->exported);
	else
	{
		i = 0;
		while (full_cmd[++i])
		{
			if (check_valid_id(full_cmd[i]))
				status = invalid_id(full_cmd[i]);
			else if (!has_equal(full_cmd[i]))
				continue ;
			else
			{	
				shell->env = add_env(shell->env, full_cmd[i]);	
				shell->exported = add_env(shell->exported, full_cmd[i]);
				//if (shell->env == NULL || shell->exported == NULL) protect final_free
			}
		}
	}
	return (status);
}
	