/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:30:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 16:51:08 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_pipe_exec_var
{
	int		pipefd[2];
	int		prev_read_fd;
	pid_t	pid;
	pid_t	*str_pid;
	int		i;
	int		expandor_check;
	int		hdoc_check;
	int		std_out;
	int		std_in;
}	t_pipe_exec_var;

typedef struct s_single_exec_var
{
	char	**hdoc;
	char	*in;
	int		is_out;
}	t_single_exec_var;

#endif