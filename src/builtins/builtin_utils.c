/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:39 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 02:12:16 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_not_found(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	invalid_id(char *id)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

//ft_num_strcmp compares the numeric strings to check the bounds

static int	ft_cmplen(char *n1, char *n2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(n1);
	len2 = ft_strlen(n2);
	if (len1 != len2)
	{
		if (len1 < len2)
			return (-1);
		else
			return (1);
	}
	return (ft_strcmp(n1, n2));
}

int	ft_num_strcmp(char *n1, char *n2)
{
	if (*n1 == '-' && *n2 != '-')
		return (-1);
	if (*n1 != '-' && *n2 == '-')
		return (1);
	if (*n1 == '-' && *n2 == '-')
		return (-ft_num_strcmp(n1 + 1, n2 + 1));
	return (ft_cmplen(n1, n2));
}

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
