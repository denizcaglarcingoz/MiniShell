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
# include <dirent.h>//not in Deniz version
# include "lexer.h"
# include "parser.h"
# include <sys/wait.h>

#define BUFFER_SIZE 4084

typedef struct s_shell
{
	char	*input;
	char	**env;
	char	**exported;
	int		exit_status;
	int		table_len;//
}	t_shell;

/* typedef enum e_token_type
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
}	t_tokens; */

/****SHELL****/
void		shell_loop(t_shell *shell);

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
t_table		*parser(t_tokens *tokens);
t_table		*table_init(t_tokens *tokens, t_table *table);
int			t_content_alloc(t_tokens *tokens, t_table *table);

// table allocs
t_table		*table_alloc(t_tokens *tokens);
t_table		struct_null(t_table table);

void			free_table(t_table *table);
// test print
int			print_tables(t_table *table);

/****EXPANSION****/
t_table			expandor(t_table table);
char 			*ft_strjoin_char(char *s1, char c);
bool			is_alfa_num(char c);
bool			arg_expand(char ***ref_content);
bool			content_check(char *content);
char			*expansion_check(char *content);
bool			redir_expand(char **content);

/****EXECUTION****/
t_table			*execution(t_table *table, t_shell *shell);// added shell
t_table			single_exec(t_table table, t_shell *shell);// added shell
t_table			*pipe_execution(t_table *tables, t_shell *shell);// added shell
void			pipe_exec_run(t_table exp_table, int table_id, char **hdoc);
void			run_command(t_table exp_table, int table_id, int pipefd1, int out_fd);
void			fork_fail(t_table *exp_table);
char			*check_in(t_table exp_table);
char			**check_hdoc(t_table exp_table);
int				output_check(t_table exp_table, int table_id);
void			inp_cmd_run(t_table exp_table, char *in, char **hdoc);
char 			*temp_hdoc(char *hdoc);

//execution execve
char			*ft_execve(char *path, char **argv);
char			*ft_pipe_execve(char *path, char **argv, int is_out);
	
// execution redirections
char			*hdoc_inp(char *h_name);
int				append_file(char *file_name, char *app_file);
int				output_file(char *file_name, char *out_file);
	
// exectution utils
t_tokens		*start_of_pipe(t_tokens *tokens, int table_id);
char 			*read_file(int fd);
int				is_builtin(char *cmd);
t_token_type	out_o_app(t_table exp_table, int table_id);
t_token_type	in_o_hdoc(t_table exp_table, int table_id);
char			*last_str(char **strs);


/****SIGNALS****/
void	sigint_handler_int(int signum);
void	sigint_handler_quit(int signum);

/***BUILT-INS****/
//char	**parse_dollar(t_table *table, char **full_cmd, t_shell *shell);

int		ft_echo(char **full_cmd);
int		ft_cd(char **full_cmd, t_shell *shell);
int		ft_pwd(void);
int		ft_exit(t_table *table, char **full_cmd, t_shell *shell);
int		ft_export(char **full_cmd, t_shell *shell);
int		ft_unset(t_table *table, char **full_cmd, t_shell *shell);

//utils
//int		check_and_run_builtins_2(t_table *table, char **full_cmd, t_shell *shell);
//int		check_and_run_builtins(t_table *table, char **full_cmd, t_shell *shell);

void	run_builtin(t_table table, t_shell *shell);//shell

void	ft_quicksort_params(char **tab, int start, int end);
int		has_equal(char *str);
void	cd_not_found(char **full_cmd);
int		invalid_id(char *id);
int		compare_names_add(char *name, char *var);


/***ENV_UTILS***/
char	**get_env(void);
void	print_env(char **env);
char	**add_env(char **env, char *variable);
char	**del_env(char **env, char *variable);
char 	*ft_getenv(char *path, char **env);

int		check_valid_id(char *s);
int		invalid_id(char *id);


/***OTHER***/
void		print_intro(void);

/***CLEAN UP***/
void	readline_error_exit(char *init_in, t_shell *shell);
void	trim_error_exit(char *init_in, t_shell *shell);
void	control_d_exit(t_shell *shell);

void	free_envs(char **env, int i);
void	free_all_env(char **env);
void	free_list(t_tokens *tokens);

void	free_t_content_alloc_and_table(t_table *table, int i);
int		ft_matrix_len(char **matrix);
void	free_content_first_allocs_only(t_table table);
void	free_matrix(char **matrix, int i);

void	free_d_str(char **str);


/* 
void	executor(t_table *table, t_shell *shell);//go
size_t		get_expanded_len(char *str, t_shell *shell);//go
char		*expander(char *str, t_shell *shell);//go  */
#endif