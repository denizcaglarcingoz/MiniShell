/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:03 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/10 19:33:49 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_empty_exp(t_shell *shell)
{
	char	curr_dir[PATH_MAX];
	char	*path;
	char	pwd_str[PATH_MAX + 4];
	char	path_str[PATH_MAX + 4];

	shell->exported = NULL;
	getcwd(curr_dir, sizeof(curr_dir));
	ft_strcpy(pwd_str, "PWD=");
	ft_strcat(pwd_str, curr_dir);
	shell->exported = add_env(shell->exported, pwd_str);
	if (shell->exported == NULL)
		return (NULL);
	shell->exported = add_empty_items(shell->exported, shell);
	if (shell->exported == NULL)
		return (NULL);
	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	ft_strcpy(path_str, "PATH=");
	ft_strcat(path_str, path);
	shell->exported = add_env(shell->exported, path_str);
	if (shell->exported == NULL)
		return (NULL);
	return (shell->exported);
}

char	**add_empty_items(char **env, t_shell *shell)
{
	env = add_env(env, "LS_COLORS=");
	if (shell->env == NULL)
		return (NULL);
	env = add_env(env, "LESSCLOSE=/usr/bin/lesspipe %s %s");
	if (shell->env == NULL)
		return (NULL);
	env = add_env(env, "LESSOPEN=| /usr/bin/lesspipe %s");
	if (shell->env == NULL)
		return (NULL);
	env = add_env(env, "SHLVL=1");
	if (shell->env == NULL)
		return (NULL);
	return (env);
}

//must check path on school machine for both init_emptys

char	**init_empty_env(t_shell *shell)
{
	char	curr_dir[PATH_MAX];
	char	*path;
	char	pwd_str[PATH_MAX + 4];
	char	path_str[PATH_MAX + 4];

	shell->env = NULL;
	getcwd(curr_dir, sizeof(curr_dir));
	ft_strcpy(pwd_str, "PWD=");
	ft_strcat(pwd_str, curr_dir);
	shell->env = add_env(shell->env, pwd_str);
	if (shell->env == NULL)
		return (NULL);
	shell->env = add_empty_items(shell->env, shell);
	if (shell->env == NULL)
		return (NULL);
	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	ft_strcpy(path_str, "PATH=");
	ft_strcat(path_str, path);
	shell->env = add_env(shell->env, path_str);
	if (shell->env == NULL)
		return (NULL);
	return (shell->env);
}

char	**get_exp(t_shell *shell)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			j;

	i = 0;
	j = -1;
	if (environ == NULL || environ[i] == NULL)
		return (init_empty_exp(shell));
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

void	init_env(t_shell *shell)
{
	shell->exit_status = 0;
	shell->env = get_env(shell);
	if (!shell->env)
	{
		free_all_env(shell->env);
		exit(EXIT_FAILURE);
	}
	shell->exported = get_exp(shell);
	if (!shell->exported)
	{
		free_all_env(shell->env);
		free_all_env(shell->exported);
		exit(EXIT_FAILURE);
	}
	shell->exported = add_env(shell->exported, "OLDPWD");
	if (shell->exported == NULL)
	{
		free_all_env(shell->env);
		free_all_env(shell->exported);
		exit(EXIT_FAILURE);
	}
	ft_quicksort_params(shell->exported, 0, ft_matrix_len(shell->exported) - 1);
}
