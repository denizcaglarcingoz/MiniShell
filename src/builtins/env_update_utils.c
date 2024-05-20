#include "minishell.h"

int	update_last_cmd(char **full_cmd, t_shell *shell)
{
	char	*comm;
	int		i;

	i = 0;
	while (full_cmd[(i + 1)])
		i++;
	comm = (char *)malloc((ft_strlen(full_cmd[i]) + 3) * sizeof(char));
	if (!comm)
	{
		free_all(shell, "env malloc failure", 127);
		return (2);
	}
	ft_strcpy(comm, "_=");
	ft_strcat(comm, full_cmd[i]);
	shell->env = add_env(shell->env, comm);
	if (!shell->env)
		free_all(shell, "env malloc failure", 127);
	free(comm);
	return (0);
}

void	init_env(t_shell *shell)
{
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
	ft_quicksort_params(shell->exported, 0, ft_matrix_len(shell->exported) - 1);
}