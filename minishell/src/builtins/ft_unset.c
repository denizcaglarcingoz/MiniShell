# include "minishell.h"

int	ft_unset(t_table *table, char **full_cmd, t_shell *shell)
{
	int	 status;
	int		i;

	(void)table;
	status = 0;
	i = 0;
		while (full_cmd[++i])
		{
			/* if (!check_valid_id(full_cmd[i]))
				status = invalid_id(full_cmd[i]); */
			if (ft_getenv(full_cmd[i], shell->env) == NULL)
				continue ;
			else
			{	
				shell->env = del_env(shell->env, full_cmd[i]);
				shell->exported = del_env(shell->exported, full_cmd[i]);
				//if (shell->env == NULL || shell->exported == NULL)
				//	free_all_and_exit
				//	ft_putstr_color_fd(1, "null\n", BOLD_BLUE);//test
			}		
		}
	return (status);
}