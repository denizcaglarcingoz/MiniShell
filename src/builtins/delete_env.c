/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:53 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:27:54 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_names(char *name, char *var)
{
	while (*name && *name != '=' && (*name == *var))
	{
		name++;
		var++;
	}
	if (*name == '=')
		return ('\0' - *var);
	else
		return (*name - *var);
}

static char	**del_env_helper(char **env, char *variable, int size)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	new_env = (char **)malloc((size) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (++i < size)
	{
		if (compare_names(env[i], variable) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				free_envs(new_env, j);
				return (NULL);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**del_env(char **env, char *variable)
{
	int		i;
	char	**new_env;

	i = 0;
	if (variable == NULL || *variable == '\0')
		return (env);
	while (env[i] != NULL)
		i++;
	new_env = del_env_helper(env, variable, i);
	free_envs(env, i);
	return (new_env);
}
