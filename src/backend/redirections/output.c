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

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
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
