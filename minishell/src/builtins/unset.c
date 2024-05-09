#include "minishell.h"

int	ft_unset(t_table *table, char **full_cmd, t_shell *shell)
{
	int	status;
	int	i;

	(void)table;
	status = 0;
	i = 0;
	while (full_cmd[++i])
	{
		if (ft_getenv(full_cmd[i], shell->env) == NULL)
			shell->exported = del_env(shell->exported, full_cmd[i]);
		else
		{
			shell->env = del_env(shell->env, full_cmd[i]);
			shell->exported = del_env(shell->exported, full_cmd[i]);
		}
		if (shell->env == NULL || shell->exported == NULL)
		{
			status = 2; //free_all_and_exit
			break ;
		}
	}
	return (status);
}
