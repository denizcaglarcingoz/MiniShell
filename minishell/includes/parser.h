#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_table
{
	char	**args;
	char	**in;
	char	**out;
	char	**my_stdin;
	char	**append;
	char	**heredoc;
	char	*err;
	char	*pipe;
	int		job_len;
	int		table_len;
	t_tokens	*tokens;
}	t_table;

typedef struct s_table_content_len
{
	int	args;
	int	in;
	int	out;
	int	append;
	int	heredoc;
	int	err;
}	t_table_content_len;



#endif