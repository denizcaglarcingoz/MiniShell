/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 05:00:59 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/05 05:07:54 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*temp_hdoc(char *hdoc)
{
	int	fd;

	fd = open("temp_hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open: temp_hdoc"), NULL);
	write(fd, hdoc, ft_strlen(hdoc));
	close(fd);
	return ("temp_hdoc");
}
