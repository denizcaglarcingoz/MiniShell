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
# include <termcap.h>//what are these last four doing?
# include <ncurses.h>
# include <sys/ioctl.h> 
# include <termios.h>
# include "parser.h"

#define BUFFER_SIZE 48

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


/****SIGNALS****/
void		sigint_handler_int(int signum);
void		sigint_handler_quit(int signum);

/***BUILT-INS****/
void	ft_exit(t_tokens *tokens);
void	ft_echo(t_tokens *tokens);
void	ft_cd(t_tokens *tokens);
void	ft_pwd(void);


/***LEXER UTILS***/
t_tokens	*token_init_string(t_tokens *c_token,char **content, t_token_type type);
int			init_loop(char **content, int d_quo_qty, int quo_qty, int i);
t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type);
t_tokens	*meta_content(t_tokens *c_token, char **input);

/***OTHER***/
void		print_intro(void);

/**testing**/
void		print_tokens(t_tokens *tokens);

/**is**/
bool is_meta_char(char is);

// PARSER
t_tokens *grammer_check(t_tokens *tokens);
t_table *parser(t_tokens *tokens);
t_table *table_init(t_tokens *tokens, t_table *table);

// TABLE ALLOCS
t_table	*table_alloc(t_tokens *tokens);
t_table	struct_null(t_table table);

// TEST PRINT
int print_tables(t_table *table);

#endif