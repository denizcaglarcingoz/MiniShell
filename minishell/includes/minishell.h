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

#define BUFFER_SIZE 48

typedef struct s_shell
{
	char	*input;
	char	**env;
	int		exit_status;
	//char	*old_pwd;
}	t_shell;

typedef enum e_token_type
{
	INITIAL, //THE FIRST PART UNTIL THE SPACE --COMMAND OR PATH ETC
	//WHITESPACE,
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

size_t	get_expanded_len(char *str, t_shell *shell);//pass in shell struct for exit size and env...make get env for ours
char	*expander(char *str, t_shell *shell);//pass in shell struct for exit size and env



/****LIST_UTILS****/
void		free_list(t_tokens **tokens);
int			ft_size(t_tokens *tokens);//DO I NEED THIS?
t_tokens	*ft_last(t_tokens *tokens); //OR THIS?
void		add_token(t_tokens **tokens, t_tokens *newnode);
t_tokens	*build_token_list(char *input);

/***ENV_UTILS***/
char	**get_env(void);
void	print_env(char **env);
char	**add_env(char **env, char *variable);
char	**del_env(char **env, char *variable);
char 	*ft_getenv(char *path, char **env);//adding a get function for our env list

/****SIGNALS****/
void		sigint_handler_int(int signum);
void		sigint_handler_quit(int signum);

/***BUILT-INS****/
void	ft_exit(t_tokens *tokens, t_shell *shell);
void	ft_echo(t_tokens *tokens);
void	ft_cd(t_tokens *tokens, t_shell *shell);
void	ft_pwd(void);

/***LEXER UTILS***/
t_tokens	*token_init_string(t_tokens *c_token,char **content, t_token_type type);
int			init_loop(char **content, int d_quo_qty, int quo_qty, int i);
t_tokens	*token_init(t_tokens *c_token, char *content, t_token_type type);
t_tokens	*meta_content(t_tokens *c_token, char **input);


void	check_and_run_builtins(t_tokens *tokens, t_shell *shell);

/***CLEAN UP***/
void    free_envs(char **env, int i);
void	free_all_env(char **env);




/***OTHER***/
void	print_intro(void);

/**testing**/
void	print_tokens(t_tokens *tokens);

/**is**/
bool	is_meta_char(char is);


#endif