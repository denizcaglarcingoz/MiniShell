/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:00 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:01 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **full_cmd)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	if (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (full_cmd[i] && *(full_cmd[i]))
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
