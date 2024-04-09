#include "../../includes/minishell.h"
/* cd - = change to previous dir. dont
	cd  or cd ~ = change to home dont need to handle see pdf //pdf says only relative or absolute path
	cd ../ or .. = one level up rel v abs path?
	cd ../../ = two lev up
	*/
//update env?
void	ft_cd(t_tokens *tokens, t_shell *shell)
{
	char *path;

	if (!tokens->next || *(tokens->next->content) == '~')//cd by itself goes to home.
		path = ft_getenv("HOME", shell->env);
	else
	{	
		if (*(tokens->next->content) != '/')
			path = ft_getenv(tokens->next->content, shell->env);
		else
			path = tokens->next->content;
	}
	if (chdir(path) != 0)
	{
		ft_putstr_color_fd(2, "Error: directory not found\n", RED);
		return ;
	}
	//test print----------------------
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	ft_putstr_color_fd(1, "current directory: ", MAGENTA);
	ft_putstr_color_fd(1, cwd, CYAN);
	ft_putchar_fd('\n', 1);
}