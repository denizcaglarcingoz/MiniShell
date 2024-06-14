/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:18 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:19 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	replace_cmd_noplus(char **cmd, t_shell *shell)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	while ((*cmd)[i])
		i++;
	//printf("here is the len: %d\n", i);
	new_cmd = (char *)malloc(sizeof(char) * i);
	if (!new_cmd)
		free_all(shell, "export malloc failed", 127);
	i = 0;
	j = 0;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '+')
			i++;
		new_cmd[j] = (*cmd)[i];
		i++;
		j++;
	}
	new_cmd[j] = '\0';
	//printf("here is the cmd: %s\n", new_cmd);
	free(*cmd);
	*cmd = NULL;
	*cmd = new_cmd;
}

int	check_valid_id(char *s, t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]) || !(s[i] == '_' || ft_isalpha(s[i])))
		return (1);
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (s[i] == '+' && s[i + 1] == '=')
	{
		replace_cmd_noplus(&s, shell);
		return (0);
	}
	i = -1;
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
			{
				if (env[i][j] == '\"')
					ft_putchar_fd('\\', 1);
				ft_putchar_fd(env[i][j], 1);
			}
			ft_putchar_fd('\"', 1);
		}
		ft_putstr_fd("\n", 1);
	}
}

int	export_loop(char *cmd, t_shell *shell)
{
	int		ret;
	//bool	plus_equal;

	ret = 0;
	//plus_equal = false;
	if (check_valid_id(cmd, shell))
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
				free_all(shell, "export malloc failed", 127);
		}
	}
	return (status);
}
