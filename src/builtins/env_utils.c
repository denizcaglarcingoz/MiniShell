/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:07 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 08:32:47 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envs(char **env, int i)
{
	int	j;

	if (env == NULL)
		return ;
	j = -1;
	while (++j < i)
	{
		free(env[j]);
		env[j] = NULL;
	}
	free(env);
	env = NULL;
}

void	free_all_env(char **env)
{
	int	j;
	int	env_len;

	if (env == NULL)
		return ;
	j = -1;
	env_len = 0;
	while (env[env_len])
		env_len++;
	while (++j < env_len)
	{
		free(env[j]);
		env[j] = NULL;
	}
	free(env);
	env = NULL;
}

int	print_env(char **env)
{
	signal(SIGPIPE, SIG_IGN);
	if (env == NULL)
		return (2);
	while (*env != NULL)
	{
		if (ft_putstr_fd_return(*env, 1) == -1)
			return (1);
		ft_putchar_fd('\n', 1);
		env++;
	}
	return (0);
}

char	**get_env(t_shell *shell)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			j;

	i = 0;
	j = -1;
	if (environ == NULL || environ[i] == NULL)
		return (init_empty_env(shell));
	while (environ[i] != NULL)
		i++;
	env = (char **)malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (++j < i)
	{
		env[j] = ft_strdup(environ[j]);
		if (!env[j])
		{
			free_envs(env, j);
			return (NULL);
		}
	}
	env[i] = NULL;
	return (env);
}
