#include "minishell.h"

void run_builtin(t_table table, t_shell *shell)//shell
{
	if (ft_strcmp(table.args[0], "exit") == 0) 
		shell->exit_status = ft_exit(&table, table.args, shell);
	else if (ft_strcmp(table.args[0], "echo") == 0)
		shell->exit_status = ft_echo(table.args);
	else if (ft_strcmp(table.args[0], "pwd") == 0)//prints cannot fail.
		ft_pwd();
	else if (ft_strcmp(table.args[0], "env") == 0)
		print_env(shell->env);
	else if (ft_strcmp(table.args[0], "cd") == 0) 
		shell->exit_status = ft_cd(table.args, shell);//malloc fail returns 2, fail to find 1, 0 good;//change value for malloc fail
	else if (ft_strcmp(table.args[0], "export") == 0)
		shell->exit_status = ft_export(table.args, shell);
	else if (ft_strcmp(table.args[0], "unset") == 0)
		shell->exit_status = ft_unset(&table, table.args, shell);
	
	free_all(shell, "no exit", 0);
	//if (shell->exit_status == 2) use malloc fail status check to free and exit if needed.
}