#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
 

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
	D_QUOTE,
	NO_TYPE

}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_table
{
	char		**args;
	char		**in;
	char		**out;
	char		**append;
	char		**heredoc;
	int			job_len;
	int			table_len;
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