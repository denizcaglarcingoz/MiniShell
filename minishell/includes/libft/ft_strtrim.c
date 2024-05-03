/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:16:51 by jhotchki          #+#    #+#             */
/*   Updated: 2024/04/29 23:32:29 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s12;
	char	*result;

	if (!s1 || *s1 == '\0')
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	s12 = (char *)s1;
	i = 0;
	j = ft_strlen(s12) - 1 ;
	while (isset(s12[i], set) && s12[i])
	{
		i++;
	}
	while (isset(s12[j], set) && s12[j])
	{
		j--;
	}
	j++;
	result = ft_substr(s12, i, j - i);
	return (result);
}
/*
int main()
{
	const char *s = "abchellocba";
	char const *set = "abc";
	char *res1 = ft_strtrim(s, set);
	printf("%s\n", res1);
	free(res1);
	return 0;
}*/
