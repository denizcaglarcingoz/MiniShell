/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_str_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:29:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/27 22:07:18 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*empty_s_quo_txt(void)
{
	char	*d_quo_specification;

	d_quo_specification = (char *)malloc(sizeof(char) * 3);
	if (d_quo_specification == NULL)
		return (NULL);
	d_quo_specification[0] = '\0';
	d_quo_specification[1] = '"';
	d_quo_specification[2] = '\0';
	return (d_quo_specification);
}

char	*empty_d_quo_txt(void)
{
	char	*d_quo_specification;

	d_quo_specification = (char *)malloc(sizeof(char) * 3);
	if (d_quo_specification == NULL)
		return (NULL);
	d_quo_specification[0] = '\0';
	d_quo_specification[1] = '"';
	d_quo_specification[2] = '\0';
	return (d_quo_specification);
}

char	*empty_dollar_txt_s(void)
{
	char	*d_quo_specification;

	d_quo_specification = (char *)malloc(sizeof(char) * 3);
	if (d_quo_specification == NULL)
		return (NULL);
	d_quo_specification[0] = '\0';
	d_quo_specification[1] = '$';
	d_quo_specification[2] = '\0';
	return (d_quo_specification);
}

char	**empty_dollar_txt_d(void)
{
	char	**dollar_specification;

	dollar_specification = (char **)malloc(sizeof(char *) * 2);
	if (dollar_specification == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	dollar_specification[0] = (char *)malloc(sizeof(char) * 3);
	if (dollar_specification == NULL)
	{
		free(dollar_specification);
		perror("malloc");
		return (NULL);
	}
	dollar_specification[0][0] = '\0';
	dollar_specification[0][1] = '$';
	dollar_specification[0][2] = '\0';
	dollar_specification[1] = NULL;
	return (dollar_specification);
}
