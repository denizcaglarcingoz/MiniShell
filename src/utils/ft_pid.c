/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:24:33 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 21:42:17 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(t_shell *shell, char *to_open)
{
	int	fd;

	fd = open(to_open, O_RDONLY);
	if (fd == -1)
		free_all(shell, "/proc/self/stat fail open :(\n", -127);
	return (fd);
}

char	*get_pidstr(char *buffer)
{
	int		i;
	char	*pid_str;

	i = 0;
	pid_str = ft_strdup("");
	if (!pid_str)
		return (NULL);
	while (buffer[i] != ' ' && buffer[i] != '\0')
	{
		pid_str = ft_strjoin_char(pid_str, buffer[i]);
		if (!pid_str)
			return (NULL);
		i++;
	}
	return (pid_str);
}

int	ft_pid(t_shell *shell)
{
	char	buffer[256];
	int		bytes_read;
	int		pid;
	int		fd;
	char	*pid_str;

	pid = -42;
	fd = ft_open(shell, "/proc/self/stat");
	bytes_read = read(fd, buffer, 255);
	if (bytes_read == -1)
		(close(fd), free_all(shell, "ftpidopen:(\n", -127));
	buffer[bytes_read] = '\0';
	close(fd);
	pid_str = get_pidstr(buffer);
	if (!pid_str)
		(close(fd), free_all(shell, "Malloc Error\n", 127));
	pid = ft_atoi(pid_str);
	free(pid_str);
	return (pid);
}
