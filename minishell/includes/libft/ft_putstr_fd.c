/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:16 by jhotchki          #+#    #+#             */
/*   Updated: 2023/09/11 19:45:38 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int len;

	len = 0;
	while (*s)
	{
		len += write(fd, s, 1);
		s++;
	}
	return (len);
}
/*int main()
{
	char *s1 = "stuff for the thing";
	ft_putstr_fd(s1, 1);
	write(1, "\n", 1);
	return 0;
}*/
