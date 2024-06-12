/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:22 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:28:24 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *path, char **env)
{
	int		i;
	size_t	path_len;

	if (path == NULL || *path == '\0')
		return (NULL);
	i = 0;
	while (env[i] && compare_names(env[i], path) != 0)
		i++;
	path_len = ft_strlen(path);
	if (env[i] == NULL)
		return (NULL);
	return (env[i] + path_len + 1);
}
