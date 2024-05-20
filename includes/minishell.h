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
# include <termcap.h>
# include <ncurses.h>
# include <sys/ioctl.h> 
# include <termios.h>
# include "parser.h"
# include "lexer.h"
# include <sys/wait.h>
# include <sys/stat.h>

# define BUFFER_SIZE 4084
# define L_MAX_STR "9223372036854775807"
# define L_MIN_STR "-9223372036854775808"

typedef struct s_shell
{
	char		*input;
	char		**env;
	char		**exported;
	int			exit_status;
	int			table_len;//
	t_table		*tables;
	t_tokens	*tokens;
}	t_shell;

/****SHELL****/
void			shell_loop(t_shell *shell);

/***LEXER UTILS***/
t_tokens		*build_token_list(char *input, t_shell *shell);
t_tokens		*token_init_string(t_tokens *c_token, char **content, \
t_token_type type);
int				init_loop(char **content, int d_quo_qty, int quo_qty, int i);
t_tokens		*token_init(t_tokens *c_token, char *content, \
t_token_type type);
t_tokens		*meta_content(t_tokens *c_token, char **input);
bool			is_meta_char(char is);
//test print
void			print_tokens(t_tokens *tokens);

/****PARSER****/
t_tokens		*grammer_check(t_tokens *tokens);
t_table			*parser(t_tokens *tokens);
t_table			*table_init(t_tokens *tokens, t_table *table);
void			t_content_alloc(t_tokens *tokens, t_table *table);

// table allocs
t_table			*table_alloc(t_tokens *tokens);
t_table			struct_null(t_table table);

void			free_table(t_table *table);
// test print
int				print_tables(t_table *table);

/****EXPANSION****/
bool			expandor(t_shell *shell, int table_num);
char			*expansion_check(char *content, t_shell *shell);
bool			arg_expand(char ***ref_content, t_shell *shell);
char			**split_join(char **content, char **exp, int add_split_from, \
t_shell *shell);
bool			redir_expand(char **content, t_shell *shell);
char			**dollar_question(t_shell *shell);
char			**exp_check(char *content, t_shell *shell);
char			*exp_s_quo(char *content, int *i, char *new_content);
char			*exp_d_quo(char *content, int *i, char *new_content, \
t_shell *shell);
char			*quo_dollar_question(t_shell *shell);

	/****Expansion Utils****/
bool			content_check(char *content);
int				d_str_len(char **str);
char			*ft_strjoin_char(char *s1, char c);
bool			str_is_alfa_num(char *str);
bool			is_alfa_num(char c);

/****EXECUTION****/
void			execution(t_shell *shell);
void			single_exec(t_shell *shell);
void			pipe_execution(t_shell *shell);
void			pipe_exec_run(t_table exp_table, int table_id, char **hdoc, \
t_shell *shell);
void			run_command(t_table exp_table, int table_id, int pipefd1, \
int out_fd);
void			fork_fail(t_table *exp_table);
char			*check_in(t_table exp_table);
char			**check_hdoc(t_table exp_table, t_shell *shell);
int				output_check(t_table exp_table, int table_id, \
t_tokens *tokens);
void			inp_cmd_run(t_table exp_table, char *in, char **hdoc, \
t_shell *shell);
char			*temp_hdoc(char *hdoc);

//execution execveclear
char			*ft_execve(char *path, char **argv, t_shell *shell);
void			ft_pipe_execve(char *path, char **argv, t_shell *shell);
// execution redirections
char			*hdoc_inp(char *h_name, t_shell *shell);
int				append_file(char *file_name, char *app_file);
int				output_file(char *file_name, char *out_file);

// exectution utils
t_tokens		*start_of_pipe(t_tokens *tokens, int table_id);
t_token_type	out_o_app(t_table exp_table, int table_id, t_tokens *tokens);
t_token_type	in_o_hdoc(t_tokens *tokens, int table_id);
char			*read_file(int fd);
char			*last_str(char **strs);
int				is_builtin(char *cmd);
int				is_directory(const char *path);

/***BUILT-INS****/

int				ft_echo(char **full_cmd);
int				ft_cd(char **full_cmd, t_shell *shell);
int				ft_pwd(void);
int				ft_exit(char **full_cmd, t_shell *shell);
int				ft_export(char **full_cmd, t_shell *shell);
int				ft_unset(t_table *table, char **full_cmd, t_shell *shell);

//built-in utils
void			run_builtin(t_table table, t_shell *shell);
void			ft_quicksort_params(char **tab, int start, int end);
int				has_equal(char *str);
void			cd_not_found(char **full_cmd);
int				invalid_id(char *id);
int				compare_names_add(char *name, char *var);
int				compare_names(char *name, char *var);
int				ft_num_strcmp(char *n1, char *n2);

/***ENV_UTILS***/
char			**get_env(void);
void			print_env(char **env);
char			**add_env(char **env, char *variable);
char			**del_env(char **env, char *variable);
char			*ft_getenv(char *path, char **env);

int				check_valid_id(char *s);
int				invalid_id(char *id);
int				update_last_cmd(char **full_cmd, t_shell *shell);
void			init_env(t_shell *shell);

/***CLEAN UP***/
void			token_list_error_exit(t_shell *shell);
void			readline_error_exit(char *init_in, t_shell *shell);
void			trim_error_exit(char *init_in, t_shell *shell);
void			control_d_exit(t_shell *shell);

void			free_envs(char **env, int i);
void			free_all_env(char **env);
void			free_list(t_tokens *tokens);

void			free_t_content_alloc_and_table(t_table *table, int i);
int				ft_matrix_len(char **matrix);
void			free_content_first_allocs_only(t_table table);
void			free_matrix(char **matrix, int i);

void			free_d_str(char **str);
void			free_all(t_shell *shell, char *print, int exit_type);

/***SIGNALS***/
void			sigint_handler_int(int signum);
void			sigint_handler_hdoc(int signum);
void			signal_handler(int signum, siginfo_t *info, void *context);
void			sigint_handler_child(int signum);

/***OTHER***/
void			print_intro(void);

#endif