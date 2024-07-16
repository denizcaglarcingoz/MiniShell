/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:35 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:27:36 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_names_add(char *name, char *var)
{
	while (*var && *name != '=' && *var != '=' && (*name == *var))
	{
		name++;
		var++;
	}
	if (*name == '=' && *var == '\0')
		return (-256);
	if (*name == '=' && (*var == '=' || (*var == '\0' && !(has_equal(var)))))
		return (0);
	if (*var == '=' && (*name == '=' || (*name == '\0' && !(has_equal(name)))))
		return (0);
	else
		return (*name - *var);
}

static int	insert_var(char **env, char **new_env, char *variable, int i)
{
	if (compare_names_add(env[i], variable) != 0)
		new_env[i] = ft_strdup(env[i]);
	else
		new_env[i] = ft_strdup(variable);
	if (!new_env[i])
	{
		free_envs(new_env, i);
		return (0);
	}
	return (1);
}

static char	**add_env_helper(char **env, \
	char *variable, int size, int flag1)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = (char **)malloc((size + 2) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (++i < size + flag1)
	{
		if (!insert_var(env, new_env, variable, i))
			return (NULL);
	}
	if (!flag1)
	{
		new_env[i] = ft_strdup(variable);
		if (!new_env[i])
		{
			free_envs(new_env, i);
			return (NULL);
		}
	}
	new_env[i + !flag1] = NULL;
	return (new_env);
}

char	**add_env(char **env, char *variable)
{
	int		i;
	bool	flag;
	char	**new_env;

	i = -1;
	flag = 0;
	if (variable == NULL || *variable == '\0')
		return (env);
	if (env)
	{
		while (env[++i] != NULL)
		{
			if (compare_names_add(env[i], variable) == 0)
				flag = 1;
			if (compare_names_add(env[i], variable) == -256)
				return (env);
		}
	}
	new_env = add_env_helper(env, variable, i - flag, flag);
	free_envs(env, i);
	return (new_env);
}
