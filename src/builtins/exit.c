/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:13 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/12 15:43:32 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_err(char **full_cmd, long int *code)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(full_cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	*code = 2;
}

int	is_all_digit(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	set_code(char **full_cmd)
{
	long int	code;

	if (!is_all_digit(full_cmd[1]))
		print_exit_err(full_cmd, &code);
	if ((full_cmd[1][0] == '-' && ft_num_strcmp(full_cmd[1], L_MIN_STR) < 0) ||
		(full_cmd[1][0] != '-' && ft_num_strcmp(full_cmd[1], L_MAX_STR) > 0))
		print_exit_err(full_cmd, &code);
	else
	{
		code = ft_atol(full_cmd[1]);
		code %= 256;
		if (code < 0)
			code += 256;
	}
	return (code);
}

void	final_free(t_shell *shell)
{
	clear_history();
	free_all_env(shell->env);
	free_all_env(shell->exported);
	free_list(shell->tokens);
	free_table(shell->tables);
}

int	ft_exit(char **full_cmd, t_shell *shell)
{
	int	code;

	ft_putstr_fd("Exiting MINISHELL!\n", 1);
	if (ft_matrix_len(full_cmd) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (full_cmd[1])
		code = set_code(full_cmd);
	else
		code = 0;
	final_free(shell);
	exit(code);
}
err