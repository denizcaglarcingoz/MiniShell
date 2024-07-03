/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:52:14 by jhotchki          #+#    #+#             */
/*   Updated: 2024/07/02 14:40:49 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest1;
	const unsigned char	*src1;

	if (!src && !dest)
		return (dest);
	dest1 = (unsigned char *)dest;
	src1 = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
/*
int main()
{
        char str[50] = "stuff for the thing";
        //char str1[40];
       // ft_memcpy(str + 11, str + 5, 19);
        ft_memcpy(str + 11, str + 5, 19);
        printf("%s\n", str);
        return 0;
}
*/
