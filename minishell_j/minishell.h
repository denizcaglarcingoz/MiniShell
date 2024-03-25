#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include "ansi_colors.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include <termcap.h>//what are these last four doing?
# include <ncurses.h>
# include <sys/ioctl.h> 
# include <termios.h>

typedef enum e_token_type
{
	INITIAL, //THE FIRST PART UNTIL THE SPACE --COMMAND OR PATH ETC
	WHITESPACE,
	PIPE,
	STRING,
	LESS,
	GREATER,
	D_LESS,
	D_GREATER,
	L_PAR,
	R_PAR,
	QUOTE,
	D_QUOTE

}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

/****SHELL****/
void		shell_loop(char **env);


/****LIST_UTILS****/
void		free_list(t_tokens **tokens);
int			ft_size(t_tokens *tokens);//DO I NEED THIS?
t_tokens	*ft_last(t_tokens *tokens); //OR THIS?
void		add_token(t_tokens **tokens, t_tokens *newnode);
t_tokens	*build_token_list(char *input);


/***FUNCTION_UTILS***/
char **get_env();
void print_env(char **env);

bool is_white_space(char is);



/****SIGNALS****/
void		sigint_handler_int(int signum);
void		sigint_handler_quit(int signum);

/***BUILT-INS****/
void	ft_exit(t_tokens *tokens);
void	ft_echo(t_tokens *tokens);
void	ft_cd(t_tokens *tokens);
void	ft_pwd(void);

void	check_and_run_builtins(t_tokens *tokens);





/***OTHER***/
void		print_intro(void);

/**testing**/
void		print_tokens(t_tokens *tokens);

/**is**/
bool is_meta_char(char is);


#endif