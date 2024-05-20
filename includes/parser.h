#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_table
{
	char		**args;
	char		**in;
	char		**out;
	char		**append;
	char		**heredoc;
	int			job_len;
	int			table_len;
}	t_table;

	//export  daria="cat deniz.txt  out.txt"

	// cat "$daria" out.txt
	// arg[0] = cat arg[1]= "cat deniz.txt  out.txt" arg[2]= out.txt

	// cat $daria"asd"$deniz out.txt
	// arg[0]= cat arg[1]= cat arg[2]= deniz.txt arg[3]= out.txt arg[4]=out.txt

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