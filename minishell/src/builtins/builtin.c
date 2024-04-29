#include "minishell.h"

void run_builtin(t_table table)
{
	if (ft_strcmp(table.args[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(table.args[0], "echo") == 0)
		ft_echo(table.args);
	// else if (ft_strcmp(table.args[0], "cd") == 0)
	// 	ft_cd(table);
	// else if (ft_strcmp(table.args[0], "pwd") == 0)
	// 	ft_pwd();
	// else if (ft_strcmp(table.args[0], "export") == 0)
	// 	ft_export(table);
	// else if (ft_strcmp(table.args[0], "unset") == 0)
	// 	ft_unset(table);
	// else if (ft_strcmp(table.args[0], "env") == 0)
	// 	ft_env();

}