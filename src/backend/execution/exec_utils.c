/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:28:41 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/25 00:33:46 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*start_of_pipe(t_tokens *tokens, int table_id)
{
	int			i;
	t_tokens	*tmp;

	tmp = tokens;
	i = 0;
	while (i < table_id)
	{
		while (tmp->type != PIPE && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->type == PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			break ;
	}
	return (tmp);
}

// char	*read_file(int fd)
// {
// 	char	buffer[BUFFER_SIZE];
// 	int		count_read;
// 	char	*read_str;

// 	read_str = ft_strdup("");//protect
// 	(count_read = read(fd, buffer, BUFFER_SIZE));
// 	while (count_read > 0)
// 	{
// 		buffer[count_read] = '\0';
// 		read_str = ft_strjoin(read_str, buffer);
// 		// protect this
// 		(count_read = read(fd, buffer, BUFFER_SIZE));
// 	}
// 	printf("inside read_file\n");
// 	return (read_str);
// }

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "bin/echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

char	*last_str(char **strs)
{
	int	i;

	i = 0;
	if (strs[0] == NULL)
		return (NULL);
	while (strs[i] != NULL)
		i++;
	return (strs[i - 1]);
}
