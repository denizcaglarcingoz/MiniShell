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


//echo has been changed....

void	replace_cmd(char ***full_cmd, int i, t_shell *shell)
{
	free((*full_cmd)[i]);
	(*full_cmd)[i] = ft_strdup("-n");
	if (!full_cmd[i])
		free_all(shell, "Malloc Error\n", 127);
}

void	handle_ns(char ***full_cmd, t_shell *shell)
{
	int i;
	int j;

	i = -1;
	while ((*full_cmd)[++i])
	{
		if ((*full_cmd)[i][0] == '-' && (*full_cmd)[i][1] == 'n')
		{
			j = 1;
			while ((*full_cmd)[i][j] == 'n')
				j++;
			if ((*full_cmd)[i][j] == '\0')
				replace_cmd(full_cmd, i, shell);
		}
	}
}

int	ft_echo(char **full_cmd, t_shell *shell)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	
	handle_ns(&full_cmd, shell);	
	if (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))
	{
		flag = true;
		while (full_cmd[i] && !ft_strcmp(full_cmd[i], "-n"))//------------------
			i++;//-----------------------------------
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
