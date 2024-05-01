#include "minishell.h"
//remove quotes in special way, check cases
//double free occurs sometimes, why, perhaps in expander switch to indexes
int	has_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
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
		while (env[i][++j] != '=' && env[i][j])
			ft_putchar_fd(env[i][j], 1);
		if (env[i][j] != '\0')
		{
			ft_putchar_fd(env[i][j], 1);
			ft_putchar_fd('\"', 1);
			while (env[i][++j])
				ft_putchar_fd(env[i][j], 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putstr_fd("\n", 1);
	}
}

int	export_loop(char *cmd, t_shell *shell)
{
	int	ret;	

	ret = 0;
	if (check_valid_id(cmd))
		ret = invalid_id(cmd);
	else if (!has_equal(cmd))
	{
		shell->exported = add_env(shell->exported, cmd);
		ft_quicksort_params(shell->exported, 0, \
		ft_matrix_len(shell->exported) - 1);
	}
	else
	{
		shell->env = add_env(shell->env, cmd);
		shell->exported = add_env(shell->exported, cmd);
		ft_quicksort_params(shell->exported, 0, \
		ft_matrix_len(shell->exported) - 1);
	}
	if (shell->env == NULL || shell->exported == NULL)
		ret = 2;
	return (ret);
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
			status = export_loop(full_cmd[i], shell);
			if (status == 2)
				break ;
		}
	}
	return (status);//status 2 is malloc fail
}
