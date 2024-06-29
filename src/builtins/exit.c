/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:13 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 17:45:46 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_err(char **full_cmd, long int *code, t_shell *shell)
{
	clear_history();
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(full_cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	*code = 2;
	free_all_env(shell->env);
	free_all_env(shell->exported);
	free_all(shell, "", 3);
	exit(2);
}

int	is_all_digit(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	set_code(char **full_cmd, t_shell *shell)
{
	long int	code;

	if (!is_all_digit(full_cmd[1]))
		print_exit_err(full_cmd, &code, shell);
	if ((full_cmd[1][0] == '-' && ft_num_strcmp(full_cmd[1], L_MIN_STR) < 0) ||
		(full_cmd[1][0] != '-' && ft_num_strcmp(full_cmd[1], L_MAX_STR) > 0))
		print_exit_err(full_cmd, &code, shell);
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
	long int	code;

	code = 0;
	if (full_cmd[1] && full_cmd[1][0] == '\0')
		print_exit_err(full_cmd, &code, shell);
	if (full_cmd[1] && !is_all_digit(full_cmd[1]))
	{
		print_exit_err(full_cmd, &code, shell);
		return (2);
	}
	if (ft_matrix_len(full_cmd) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (full_cmd[1])
		code = set_code(full_cmd, shell);
	final_free(shell);
	// printf("exit\n");
	exit(code);
}
