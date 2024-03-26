/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:02:53 by jhotchki          #+#    #+#             */
/*   Updated: 2023/09/11 19:32:20 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	int len;

	len = 0;
	len += write(fd, &c, 1);
	return (len);
}
/*
int main()
{
		ft_putchar_fd('z', 2);
	return 0;
}*/
