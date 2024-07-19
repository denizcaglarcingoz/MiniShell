/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:00 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 08:33:24 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_cmd(char ***full_cmd, int i, t_shell *shell)
{
	char	*temp;

	temp = ft_strdup("-n");
	if (!temp)
		free_all(shell, "Malloc Error\n", 127);
	free((*full_cmd)[i]);
	(*full_cmd)[i] = temp;
}

void	handle_ns(char ***full_cmd, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while ((*full_cmd)[++i])
	{
		if ((*full_cmd)[i][0] == '-' && (*full_cmd)[i][1] == 'n')
		{
			j = 1;
			while ((*full_cmd)[i][j] == 'n')
				j++;
			if ((*full_cmd)[i][j] == '\0')
				replace_cmd(full_cmd, i, shell);
			else
				break ;
		}
		else
			break ;
	}
}

int	ft_echo(char **full_cmd, t_shell *shell)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	signal(SIGPIPE, SIG_IGN);
	handle_ns(&full_cmd, shell);
	if (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))
	{
		flag = true;
		while (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))
			i++;
	}
	while (full_cmd[i])
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
