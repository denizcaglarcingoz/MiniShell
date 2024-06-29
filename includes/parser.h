/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:30:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/26 14:11:23 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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