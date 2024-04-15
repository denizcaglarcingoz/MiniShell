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
# include <dirent.h>
# include "parser.h"

#define BUFFER_SIZE 48

typedef struct s_shell
{
	char	*input;
	char	**env;
	int		exit_status;
	int		table_len;
	//char	*old_pwd;
}	t_shell;

typedef enum e_token_type
{
	INITIAL, //THE FIRST PART UNTIL THE SPACE --COMMAND OR PATH ETC
	PIPE,
	STRING,
	LESS,
	GREATER,
	D_LESS,
	D_GREATER,
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
void		shell_loop(t_shell *shell);
size_t		get_expanded_len(char *str, t_shell *shell);
char		*expander(char *str, t_shell *shell);

/***LEXER UTILS***/
t_tokens	*build_token_list(char *input);
t_tokens	*token_init_string(t_tokens *c_token,char **content, t_token_type type);
int			init_loop(char **content, int d_quo_qty, int quo_qty, int i);
t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type);
t_tokens	*meta_content(t_tokens *c_token, char **input);
bool		is_meta_char(char is);
//test print
void	print_tokens(t_tokens *tokens);

/****PARSER****/
t_tokens	*grammer_check(t_tokens *tokens);
t_table		*parser(t_tokens *tokens, t_shell *shell);
t_table		*table_init(t_tokens *tokens, t_table *table);
int			t_content_alloc(t_tokens *tokens, t_table *table);

// table allocs
t_table		*table_alloc(t_tokens *tokens, t_shell *shell);
t_table		struct_null(t_table table);
// test print
int			print_tables(t_table *table);


/****SIGNALS****/
void	sigint_handler_int(int signum);
void	sigint_handler_quit(int signum);

/***BUILT-INS****/
void	check_and_run_builtins(t_tokens *tokens, t_shell *shell, t_table *table);
void	ft_exit(t_tokens *tokens, t_shell *shell, t_table *table);
void	ft_echo(t_tokens *tokens);
void	ft_cd(t_tokens *tokens, t_shell *shell);
void	ft_pwd(void);

/***ENV_UTILS***/
char	**get_env(void);
void	print_env(char **env);
char	**add_env(char **env, char *variable);
char	**del_env(char **env, char *variable);
char 	*ft_getenv(char *path, char **env);



/***OTHER***/
void		print_intro(void);

/***CLEAN UP***/
void	early_error_exit(char *init_in, t_shell *shell);
void	free_envs(char **env, int i);
void	free_all_env(char **env);
void	free_list(t_tokens **tokens);

void	free_t_content_alloc_and_table(t_table *table, int i);
int		ft_matrix_len(char **matrix);
void	free_content_first_allocs_only(t_table table);
void	free_matrix(char **matrix, int i);

#endif