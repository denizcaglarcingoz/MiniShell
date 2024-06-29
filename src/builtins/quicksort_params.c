/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:30 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/29 02:12:47 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_2(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2) && *s1 != '=')
	{
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 == '=')
		return (0);
	else if (*s1 == '=')
		return ('\0' - *s2);
	else if (*s2 == '=')
		return (*s1 - '\0');
	else
		return (*s1 - *s2);
}

void	str_swap(char **s1, char **s2)
{
	char	*hold;

	hold = *s1;
	*s1 = *s2;
	*s2 = hold;
}

int	partition(char **tab, int start, int end)
{
	char	*pivot;
	int		i;
	int		j;

	j = start;
	i = start -1;
	pivot = tab[end];
	while (j <= end - 1)
	{
		if (ft_strcmp_2(tab[j], pivot) < 0)
		{
			i++;
			str_swap(&tab[i], &tab[j]);
		}
		j++;
	}
	str_swap(&tab[i + 1], &tab[end]);
	return (i + 1);
}

void	ft_quicksort_params(char **tab, int start, int end)
{
	int	p;

	if (start < end)
	{
		p = partition(tab, start, end);
		ft_quicksort_params(tab, start, p - 1);
		ft_quicksort_params(tab, p + 1, end);
	}
}
