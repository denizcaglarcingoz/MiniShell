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
# include "lexer.h"
# include <sys/wait.h>

#define BUFFER_SIZE 4084

/****SHELL****/
void			shell();

//  GENERAL UTILS
void	free_d_str(char **str);

/****LIST_UTILS****/
void			free_list(t_tokens *tokens);
int				ft_size(t_tokens *tokens);//DO I NEED THIS?
t_tokens		*ft_last(t_tokens *tokens); //OR THIS?
void			add_token(t_tokens **tokens, t_tokens *newnode);
t_tokens		*build_token_list(char *input);

/****SIGNALS****/
void			sigint_handler_int(int signum);
void			sigint_handler_quit(int signum);

/***LEXER UTILS***/
t_tokens		*token_init_string(t_tokens *c_token,char **content, t_token_type type);
int				init_loop(char **content, int d_quo_qty, int quo_qty, int i);
t_tokens		*token_init(t_tokens *c_token, char *content, t_token_type type);
t_tokens		*meta_content(t_tokens *c_token, char **input);

/***OTHER***/
void			print_intro(void);

/**is**/
bool			is_meta_char(char is);

//	PARSER
t_tokens		*grammer_check(t_tokens *tokens);
t_table			*parser(t_tokens *tokens);
t_table			*table_init(t_tokens *tokens, t_table *table);
void			t_content_alloc(t_tokens *tokens, t_table *table);

//	PARSER TABLE ALLOCS
t_table			*table_alloc(t_tokens *tokens);
t_table			struct_null(t_table table);

//	PARSER UTILS
void			free_table(t_table *table);

	//EXPANSION
t_table			expandor(t_table table);
char 			*ft_strjoin_char(char *s1, char c);
bool			is_alfa_num(char c);
bool			arg_expand(char ***ref_content);
bool			content_check(char *content);
char			*expansion_check(char *content);
bool			redir_expand(char **content);
/***BUILT-INS****/
void			run_builtin(t_table table);
int				ft_echo(char **full_cmd);
char			**get_full_env(char **new_env);
char			*get_env(char *key);
void			ft_env();
void			free_env();
char			**ft_d_strdup(char **env);

//	EXECUTION
t_table			*execution(t_table *table);
t_table			single_exec(t_table table);
t_table			*pipe_execution(t_table *tables);
void			pipe_exec_run(t_table exp_table, int table_id, char **hdoc);
void			run_command(t_table exp_table, int table_id, int pipefd1, int out_fd);
void			fork_fail(t_table *exp_table);
char			*check_in(t_table exp_table);
char			**check_hdoc(t_table exp_table);
int				output_check(t_table exp_table, int table_id);
void			inp_cmd_run(t_table exp_table, char *in, char **hdoc);
char 			*temp_hdoc(char *hdoc);

	//EXECUTION EXECVE
char			*ft_execve(char *path, char **argv);
char			*ft_pipe_execve(char *path, char **argv, int is_out);
	
	// EXECUTION REDIRECTIONS
char			*hdoc_inp(char *h_name);
int				append_file(char *file_name, char *app_file);
int				output_file(char *file_name, char *out_file);
	
	// EXECUTION UTILS
t_tokens		*start_of_pipe(t_tokens *tokens, int table_id);
char 			*read_file(int fd);
int				is_builtin(char *cmd);
t_token_type	out_o_app(t_table exp_table, int table_id);
t_token_type	in_o_hdoc(t_table exp_table, int table_id);
char			*last_str(char **strs);

/**testing**/
void			print_tokens(t_tokens *tokens);
int				print_tables(t_table *table);

#endif
