/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:53:53 by dcingoz           #+#    #+#             */
/*   Updated: 2024/04/25 20:46:45 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*app_strjoin(char *s1, char const *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s2)
		return (NULL);
	if (!s1 && s2)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	s2_len = len;
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
	{
		printf("app_strjoin error\n");
		perror("Malloc Error\n");
		return (NULL);
	}
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

int read_loop(int fd, char **full_file, int *len)
{
	char	buffer[BUFFER_SIZE];
	int		count_read;
	
	*len = 1;
	while ((count_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		printf("inside count_read: %d\n", count_read);
        *full_file = app_strjoin(*full_file, buffer, count_read);
        if (*full_file == NULL) {
            return 1; // Error occurred while appending to full_file
        }
    }
	printf("outside count_read: %d\n", count_read);
	return (0);
}

int	append_file(char *file_name, char *app_file)
{
	int		fd;
	int		len;
	int		bytes_read;
	char	*full_file;

	printf("file_name: a%sa\n", file_name);
	full_file = ft_strdup("");
	if (access(file_name, F_OK) == 0)
	{
		printf("file exists\n");
		fd = open(file_name, O_RDONLY);
	}
	else
	{
		printf("file does not exist\n");
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		len = -1;
	}
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (app_file == NULL)
	{
		close(fd);
		return (0);
	}
	if (read_loop(fd, &full_file, &len) == 1)
		return (1);
	printf("full_file: %s\n", full_file);
	close(fd);
	full_file = app_strjoin(full_file, app_file, ft_strlen(app_file) + 1);
	if (full_file == NULL)
		return (1);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = ft_strlen(full_file);
	bytes_read = write(fd, full_file, len);
	if (bytes_read == -1)
	{
		perror("write");
		close(fd);
		return(1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (1);
	}
	return (0);
}

// TEST

// int main (int argc, char **argv)
// {
// 	char *file_name = "file.txt";
// 	char *inp_file = argv[1];
// 	int i = argc;
// 	i = 4;
// 	if (append_file(file_name, inp_file) == -1)
// 	{
// 		//error;
// 		return(1);
// 	}
	
// 	//printf("%s\n", inp_file);
// 	return (0);
// }


