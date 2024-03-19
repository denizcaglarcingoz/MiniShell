#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ansi_colors.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <termcap.h>//what are these last four doing?
# include <ncurses.h>
# include <sys/ioctl.h> 
# include <termios.h>

typedef enum e_token_type
{
	WHITESPACE,
	PIPE,
	STRING,
	LESS,
	GREATER,
	D_LESS,
	D_GREATER,
	L_PAR,
	R_PAR

}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

/****SHELL****/
void	shell_loop();


/****LIST_UTILS****/
void		free_list(t_tokens **tokens);
int			ft_size(t_tokens *tokens);//DO I NEED THIS?
t_tokens	*ft_last(t_tokens *tokens); //OR THIS?
void		add_token(t_tokens **tokens, t_tokens *newnode);
t_tokens		build_token_list(char *input);

/****SIGNALS****/
void sigint_handler_int(int signum);
void sigint_handler_quit(int signum);

/***OTHER***/
void	print_intro(void);

/**testing**/
void	print_tokens(t_token *tokens);


#endif