/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:43 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/13 14:06:27 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_exit_code(t_shell *shell, pid_t pid)
{
	int status;
	pid_t wait_result = waitpid(pid, &status, 0);

	if (wait_result == pid)
	{
		if (WIFEXITED(status))
		{
		    int child_exit_code = WEXITSTATUS(status);
			shell->exit_status = child_exit_code;
		}
		else
		    shell->exit_status = 127;
	}
	else
	    perror("waitpid");
}