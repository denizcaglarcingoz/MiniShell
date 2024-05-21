#include "minishell.h"

char	*get_update_cmd(char **full_cmd, t_shell *shell)
{
	int		i;
	char	*command;

	i = 0;
	while (full_cmd[(i + 1)])
		i++;
	command = ft_strdup(full_cmd[i]);
	if (!command)
		free_all(shell, "get_curr_cmd malloc failure", 127);
	return (command);
}

int	update_last_cmd(char *update_cmd, t_shell *shell)
{
	char	*comm;

	comm = (char *)malloc((ft_strlen(update_cmd) + 3) * sizeof(char));
	if (!comm)
	{
		free_all(shell, "env malloc failure", 127);
		return (2);
	}
	ft_strcpy(comm, "_=");
	ft_strcat(comm, update_cmd);
	shell->env = add_env(shell->env, comm);
	if (shell->env == NULL)
	{
		free(comm);
		free_all(shell, "env malloc failure", 127);
	}
	free(comm);
	comm = NULL;
	free(update_cmd);
	update_cmd = NULL;
	return (0);
}

void	init_env(t_shell *shell)
{
	shell->update_cmd = NULL;
	shell->exit_status = 0;
	shell->env = get_env();
	if (!shell->env)
		exit(EXIT_FAILURE);
	shell->exported = get_env();
	if (!shell->exported)
	{
		free_all_env(shell->env);
		exit(EXIT_FAILURE);
	}
	shell->exported = del_env(shell->exported, "_");
	shell->env = add_env(shell->env, "_=paco");
	ft_quicksort_params(shell->exported, 0, ft_matrix_len(shell->exported) - 1);
}
