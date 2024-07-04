/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_in_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:14:55 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 01:15:32 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	not_in_file_p(char **in, t_shell *shell)
{
	int	i;

	i = 0;
	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break ;
		i++;
	}
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 127);
}

void	not_in_file(char **in, t_shell *shell)
{
	int	i;

	i = 0;
	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break ;
		i++;
	}
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 0);
}
