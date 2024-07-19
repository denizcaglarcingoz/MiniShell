/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:30:54 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/19 10:03:11 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
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
# include "execution.h"
# include <sys/wait.h>
# include <sys/stat.h>

# define BUFFER_SIZE 4084
# define L_MAX_STR "9223372036854775807"
# define L_MIN_STR "-9223372036854775808"

extern pid_t	g_sig_int;

typedef struct s_shell
{
	char				*input;
	char				**env;
	char				**exported;
	int					exit_status;
	int					table_len;
	t_table				*tables;
	t_tokens			*tokens;
	char				**hdoc;
	int					pipe_hdoc_sig;
	int					table_id;
	int					in_fd;
	int					out_fd;
	int					pid;
	int					exp_space_flag_start;
	int					exp_space_flag_end;
	t_pipe_exec_var		exec;
	t_single_exec_var	var;
}	t_shell;

/****SHELL****/
void			shell_loop(t_shell *shell);

/***LEXER UTILS***/
t_tokens		*build_token_list(char *input, t_shell *shell);
t_tokens		*token_init_string(t_tokens *c_token, char **inp, \
t_token_type type);
int				init_loop(char **inp, int d_quo_qty, int quo_qty, int i);
t_tokens		*token_init(t_tokens *c_token, char *content, \
t_token_type type);
t_tokens		*meta_content(t_tokens *c_token, char **input);
bool			is_meta_char(char is);
bool			is_white_space(char c);

//lexer init loop utils
void			if_dquo(int *first_quo, int *d_quo_qty);
void			if_squo(int *first_quo, int *quo_qty);
int				if_wspace(int first_quo, int quo_qty, int d_quo_qty);
int				if_quo_null(int first_quo, int quo_qty, int d_quo_qty, int *i);
int				if_meta(int first_quo, int quo_qty, int d_quo_qty);

/****PARSER****/
t_tokens		*grammer_check(t_tokens *tokens, int *exit_status);
t_tokens		*token_content_check(t_tokens *tokens, int *exit_status);
t_table			*parser(t_tokens *tokens, t_shell *shell);
t_table			*table_init(t_tokens *tokens, t_table *table, t_shell *shell);
int				t_content_alloc(t_tokens *tokens, t_table *table);

// table allocs
t_table			*table_alloc(t_tokens *tokens, t_shell *shell);
t_table			struct_null(t_table table);
void			free_table(t_table *table);

/****EXPANSION****/
bool			expandor(t_shell *shell, int table_num);
bool			expandor_hdoc(t_shell *shell, int table_num);
bool			arg_expand(char ***ref_content, t_shell *shell);
char			**split_join(char **content, char **exp, int add_split_from, \
t_shell *shell);
bool			redir_expand(char **content, t_shell *shell);
void			to_exp_fail(char **new_cntnt, char *cntnt, t_shell *shell);
char			**dollar_question(t_shell *shell);
char			**exp_check(char *content, t_shell *shell);
char			*exp_s_quo(char *content, int *i, char *new_content);
char			*exp_d_quo(char *content, int *i, char *new_content, \
t_shell *shell);
char			*quo_dollar_question(int *i, char *new_cntnt, t_shell *shell);
bool			hdoc_expand(char **content, t_shell *shell);
char			*hdoc_exp_d_quo(char *cntnt, int *i, \
char *new_cntnt, t_shell *shell);
char			*hdoc_exp_s_quo(char *cntnt, int *i, \
char *new_cntnt, t_shell *shell);
void			hdoc_new_content_dquo(char ***new_content, char **content, \
int *i, t_shell *shell);
void			hdoc_new_content_squo(char ***new_content, \
char **content, int *i, t_shell *shell);

/****Expansion Utils****/
bool			content_check(char *content);
int				d_str_len(char **str);
char			*ft_strjoin_char(char *s1, char c);
bool			str_is_alfa_num(char *str);
bool			is_alfa_num(char c);
void			len_loop(char **content, int *k);
void			len_loop_2(char **content, int *k);
void			free_content(char **content);
char			**exp_check(char *content, t_shell *shell);
char			**exp_dollar(char *content, int *i,
					char **new_content, t_shell *shell);
char			*empty_s_quo_txt(void);
char			*empty_d_quo_txt(void);
char			*empty_dollar_txt_s(void);
char			**empty_dollar_txt_d(void);
char			*empty_txt_nothing(void);
int				free_d_str_int(char **str);
char			**one_dollar(char **new_content, t_shell *shell, int *i);
char			**word_split(char *new_exp);
void			empt_str_dup(char **content, char ***new_content, \
int *k, t_shell *shell);
void			n_content_dup(char *content, char ***new_content, \
int *k, t_shell *shell);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*hdoc_in_exp(t_shell *shell, char *hdoc, char *non_exp_hdoc);
char			*get_last_non_exp_hdoc(t_table table, t_shell *shell);

/****ADD NEW CONTENT****/
char			**add_new_content(char **new_content,
					char **d_exp, t_shell *shell);
void			first_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell);
void			second_loops(char ***new_content, char ***d_exp, \
char ***joined, t_shell *shell);

/****ADD NEW CONTENT UTILS****/
void			joined_free(char ***joined, t_shell *shell, \
int new_content_len, char **new_content);
int				free_d_str_int(char **str);

/****REDIRECTION****/
char			*is_dollar(char *hdoc);
char			*get_last_non_exp_hdoc(t_table table, t_shell *shell);
int				quote_check(char *non_exp_hdoc);
char			*temp_init(t_shell *shell, char *hdoc, int *i);
char			*get_dollar_name(t_shell *shell, char *hdoc, int *i);
char			*hdoc_in_dollar(t_shell *shell, char *hdoc, int *i);
char			*hdoc_inenv_loop(t_shell *shell, char *dollar);
void			hdoc_in_question(t_shell *shell, char **hdoc, int *i);
bool			ambigous_return(char **exp, t_shell *shell, \
char **content, int i);

/****EXECUTION****/
void			execution(t_shell *shell);
void			ft_pipe_execve(char *path, char **argv, t_shell *shell);
void			pipe_execution(t_shell *shell, t_pipe_exec_var *exec);
void			pipe_exec_run(t_table exp_table, int table_id, \
t_shell *shell, char *in);
pid_t			pipe_fork(t_shell *shell, int pipefd[2]);
void			exec_init(t_pipe_exec_var *exec, t_shell *shell);

//single execution
void			single_exec(t_shell *shell);
char			*ft_execve(char *path, char **argv, t_shell *shell);
void			inp_cmd_run(t_table exp_table, char *in, char **hdoc, \
t_shell *shell);

// execution redirections
char			*hdoc_inp(char *h_name, t_shell *shell);
int				output_file(char *file_name, char *out_file);
int				output_check(t_table exp_table, int table_id, \
t_tokens *tokens);
char			*check_in(t_table exp_table);
char			**check_hdoc(t_table exp_table, t_shell *shell);
int				fd_write_hdoc(char *hdoc);

// exectution utils
t_tokens		*start_of_pipe(t_tokens *tokens, int table_id);
t_token_type	out_o_app(t_table exp_table, int table_id, t_tokens *tokens);
t_token_type	in_o_hdoc(t_tokens *tokens, int table_id);
char			*last_str(char **strs);
int				is_builtin(char *cmd);
int				is_directory(const char *path);
int				ft_access(char *path, char **argv, t_shell *shell);
void			free_d_all(char **all_paths,
					char *msg, t_shell *shell, int type);
void			get_exit_code(t_shell *shell, pid_t pid);
void			get_exit_code_p(t_shell *shell, t_pipe_exec_var *exec);
void			path_run_signals(pid_t pid, t_shell *shell);
int				all_path_check(char *all_path);
char			*it_is_directory(char *first_arg, t_shell *shell);
void			null_path(char *argv, t_shell *shell);
void			ft_access_execve(char *path, char **argv, t_shell *shell);
char			*check_hdoc_p(t_table table, t_shell *shell);
void			not_in_file(char **in, t_shell *shell);
void			not_in_file_p(char **in, t_shell *shell, int table_num);
char			**app_assign_new(char **new, char **str, char *path_add);
char			**append_path(char **str, char *path_add);
int				is_hdoc_exist(t_shell *shell);
int				pipe_hdocs(t_shell *shell);
void			pipe_closing_sigs(t_shell *shell, t_pipe_exec_var *exec);
void			pipe_closing_args(t_shell *shell, t_pipe_exec_var *exec);
void			child_out_check(t_shell *shell, \
int pipefd[2], int prev_read_fd, int i);
void			single_exec_run(t_shell *shell, t_single_exec_var *var);
int				dot_check(char *first_arg, t_shell *shell);
void			print_is_directory(char *redir);

/***BUILT-INS****/

int				ft_echo(char **full_cmd, t_shell *shell);
int				ft_cd(char **full_cmd, t_shell *shell);
int				ft_pwd(t_shell *shell);
int				ft_exit(char **full_cmd, t_shell *shell);
int				ft_export(char **full_cmd, t_shell *shell);
int				ft_unset(char **full_cmd, t_shell *shell);

//built-in utils
void			run_builtin(t_table table, t_shell *shell);
void			ft_quicksort_params(char **tab, int start, int end);
int				has_equal(char *str);
void			cd_not_found(char *path);
int				invalid_id(char *id);
int				compare_names_add(char *name, char *var);
int				compare_names(char *name, char *var);
int				ft_num_strcmp(char *n1, char *n2);
int				no_equal_case(t_shell *shell, char *var);
int				handle_twodotempty(t_shell *shell);
void			cd_dash_putpath(char *path);
int				set_nullpwd(t_shell *shell);

/***ENV_UTILS***/
char			**get_exp(t_shell *shell);
char			**get_env(t_shell *shell);
int				print_env(char **env);
char			**init_empty_env(t_shell *shell);
char			**add_empty_items(char **env, t_shell *shell);
char			**add_env(char **env, char *variable);
char			**del_env(char **env, char *variable);
char			*ft_getenv(char *path, char **env);
int				check_valid_id(char **full_cmd, int j, t_shell *shell);
int				invalid_id(char *id);
void			init_env(t_shell *shell);

/***CLEAN UP***/
void			token_list_error_exit(t_shell *shell);
void			readline_error_exit(char *init_in, t_shell *shell);
void			trim_error_exit(char *init_in, t_shell *shell);
void			control_d_exit(t_shell *shell, char *init_in);
void			free_envs(char **env, int i);
void			free_all_env(char **env);
void			free_list(t_tokens *tokens);
void			free_t_content_alloc_and_table(t_table *table, int i);
int				ft_matrix_len(char **matrix);
void			free_content_first_allocs_only(t_table *table);
void			free_matrix(char **matrix, int i);
void			free_d_str(char **str);
void			free_d_str_till(char **content, int i);
void			free_all(t_shell *shell, char *print, int exit_type);
void			close_std_fd(void);

/***SIGNALS***/
void			sigint_handler_int(int signum);
void			sigint_handler_hdoc(int signum);
void			signal_handler(int signum, siginfo_t *info, void *context);
void			sigint_handler_child(int signum);
void			sigint_handler_int_exec(int signum);
void			sigint_handler_quit(int signum);
void			sigpipe_handler(int signum);
void			sigusr1_handler(int signum);
void			sigint_handler_sigint(int signum);
int				ft_putstr_fd_return(char *s, int fd);

/***SIGNAL UTILS***/
int				ft_pid(t_shell *shell);

/***TESTING***/
int				print_tables(t_table *table);
void			print_tokens(t_tokens *tokens);
void			print_d_str(char **str);

#endif