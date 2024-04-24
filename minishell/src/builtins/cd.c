#include "../../includes/minishell.h"
/* cd - = goes to old pwd.
	cd  or cd ~ = change to home dont need to handle see pdf //pdf says only relative or absolute path
	cd ../ or .. = one level up rel v abs path?
	cd ../../ = two lev up
	*/
//update env?
void	ft_cd(t_table *table, char **full_cmd, t_shell *shell)
{
	char *path;
	char cwd[PATH_MAX];

	(void)table;
	(void)shell;
	getcwd(cwd, sizeof(cwd));
//	if (!full_cmd[1] || full_cmd[1][0] == '~')//cd by itself goes to home.
	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~')//cd by itself goes to home.
		path = ft_getenv("HOME", shell->env);
	else
	{	
		if (full_cmd[1][0] != '/')
			path = ft_getenv(full_cmd[1], shell->env);
		else
			path = full_cmd[1];
	}
	if (chdir(path) != 0)
	{
		ft_putstr_color_fd(2, "Error: directory not found\n", RED);
		return ;
	}
	//test print----------------------
	
/* 	getcwd(cwd, sizeof(cwd));
	ft_putstr_color_fd(1, "current directory: ", MAGENTA);
	ft_putstr_color_fd(1, cwd, CYAN);
	ft_putchar_fd('\n', 1); */
}