/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:16 by jhotchki          #+#    #+#             */
/*   Updated: 2024/07/19 08:29:46 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	while (*s)
	{
		len += write(fd, s, 1);
		s++;
	}
	return (len);
}

int	ft_putstr_fd_return(char *s, int fd)
{
	int	len;

	len = 0;
	while (*s)
	{
		len = write(fd, s, 1);
		if (len == -1)
			return (-1);
		s++;
	}
	return (len);
}
