#include "../../includes/minishell.h"
/* cd - = change to previous dir.
	cd  or cd ~ = change to home
	cd ../ or .. = one level up
	cd ../../ = two lev up
	*/
//update env?
void	ft_cd(t_tokens *tokens)
{
	char *path;

	if (!tokens->next || *(tokens->next->content) == '~')//cd by itself goes to home.
		path = getenv("HOME");
	else
	{	
		if (*(tokens->next->content) != '/')
			path = getenv(tokens->next->content);
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