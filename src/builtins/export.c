/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:18 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 05:47:16 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_cmd_noplus(char **cmd, t_shell *shell)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	while ((*cmd)[i])
		i++;
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
	free(*cmd);
	*cmd = new_cmd;
}

int	check_valid_id(char **full_cmd, int j, t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_isdigit(full_cmd[j][i]) || !(full_cmd[j][i] == '_' \
	|| ft_isalpha(full_cmd[j][i])))
		return (1);
	while (ft_isalnum(full_cmd[j][i]) || full_cmd[j][i] == '_')
		i++;
	if (full_cmd[j][i] == '+' && full_cmd[j][i + 1] == '=')
	{
		replace_cmd_noplus(&full_cmd[j], shell);
		return (0);
	}
	i = -1;
	while (full_cmd[j][++i] && full_cmd[j][i] != '=')
	{
		if (!(ft_isalnum(full_cmd[j][i])) && !(full_cmd[j][i] == '_'))
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

int	export_loop(char **full_cmd, int i, t_shell *shell)
{
	int		ret;

	ret = 0;
	if (check_valid_id(full_cmd, i, shell))
		ret = invalid_id(full_cmd[i]);
	else if (!has_equal(full_cmd[i]))
	{
		shell->exported = add_env(shell->exported, full_cmd[i]);
		if (shell->exported == NULL)
		{
			free_all_env(shell->env);
			return (2);
		}
		ft_quicksort_params(shell->exported, 0, \
		ft_matrix_len(shell->exported) - 1);
	}
	else
	{
		if (no_equal_case(shell, full_cmd[i]))
			return (2);
	}
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
			status = export_loop(full_cmd, i, shell);
			if (status == 2)
			{
				perror("env malloc failure\n");
				rl_clear_history();
				free_list(shell->tokens);
				free_table(shell->tables);
				exit(1);
			}
		}
	}
	return (status);
}
