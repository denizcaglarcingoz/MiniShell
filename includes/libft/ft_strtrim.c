/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:16:51 by jhotchki          #+#    #+#             */
/*   Updated: 2024/06/28 02:36:01 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
	size_t	j;
	char	*s12;
	char	*result;
	int		t;

	if (s1[0] == '\0')
		return (ft_strdup(""));
	if (!s1)
		return (NULL);
	t = 0;
	while (s1[t] != '\0' && is_white_space(s1[t]))
		t++;
	if (s1[t] == '\0')
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	s12 = (char *)s1;
	j = ft_strlen(s12) - 1 ;
	while (isset(s12[t], set) && s12[t])
		t++;
	while (isset(s12[j], set) && s12[j])
		j--;
	return (j++, result = ft_substr(s12, t, j - t), result);
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
