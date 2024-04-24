#include "../../includes/minishell.h"
/* cd - = goes to old pwd.
	cd  or cd ~ = change to home dont need to handle see pdf //pdf says only relative or absolute path
	cd ../ or .. = one level up rel v abs path?
	cd ../../ = two lev up
	*/
//update env?

void	update_pwds(t_shell *shell)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*temp;
	//char 	*old;
	
	i = -1;
	//old = ft_getenv("PWD", shell->env);
	getcwd(cwd, sizeof(cwd));
	//printf("%s\n", cwd);
	while (shell->env[++i])
	{
	/* 	if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
		{
			temp = ft_strjoin("OLDPWD=", old);
			free(shell->env[i]);
			shell->env[i] = temp;
		} */
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			temp = ft_strjoin("PWD=", cwd);
			
			free(shell->env[i]);
			shell->env[i] = temp;
			//printf("%s\n", shell->env[i]);
		}
	}
}

void	relative_old_home(char **full_cmd, t_shell *shell)
{
	char *path;

	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~')//cd by itself goes to home.
		path = ft_getenv("HOME", shell->env);
	else if (**(full_cmd + 1) == '-')
		path = ft_getenv("OLDPWD", shell->env);
	else
		path = full_cmd[1];
	if (chdir(path) != 0)
		ft_putstr_color_fd(2, "Error: directory not found\n", RED);
}


void	ft_cd(t_table *table, char **full_cmd, t_shell *shell)
{
	char 	*path;
	char	*curr_dir;
	//char	cwd[PATH_MAX];
	
	(void)table;	
	if (!(*(full_cmd + 1)) || **(full_cmd + 1) == '~' ||  **(full_cmd + 1) == '/')//cd by itself goes to home.
		relative_old_home(full_cmd, shell);
	else
	{
		curr_dir = getcwd(NULL, 0);
		path = malloc(ft_strlen(curr_dir) + ft_strlen(full_cmd[1]) + 2);
		ft_strcpy(path, curr_dir);
		ft_strcat(path,"/");
		ft_strcat(path, full_cmd[1]);
		free(curr_dir);
		if (chdir(path) != 0)
			ft_putstr_color_fd(2, "Error: directory not found\n", RED);
		free(path);
	}
	update_pwds(shell);
}
	
	//test print----------------------
	//char 	cwd[PATH_MAX];
	
/* 	getcwd(cwd, sizeof(cwd));
	ft_putstr_color_fd(1, "current directory: ", MAGENTA);
	ft_putstr_color_fd(1, cwd, CYAN);
	ft_putchar_fd('\n', 1); */