/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:30:29 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 14:45:52 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_checks(int written_size, int fd)
{
	if (written_size == -1)
	{
		perror("write");
		close(fd);
		return (1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (1);
	}
	return (0);
}

int	output_file(char *file_name, char *out_file)
{
	int	fd;
	int	len;
	int	written_size;

	if (is_directory(file_name) == 1)
		return (print_is_directory(file_name), 1);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (out_file == NULL)
	{
		close(fd);
		return (0);
	}
	len = ft_strlen(out_file);
	written_size = write(fd, out_file, len);
	if (do_checks(written_size, fd))
		return (1);
	return (0);
}
