/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:00:13 by jhotchki          #+#    #+#             */
/*   Updated: 2023/09/19 07:30:21 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
int main()
{
		int c = '9';
		printf("%d\n", ft_isdigit(c));
		printf("%d\n", isdigit(c));
		return 0;
}*/
