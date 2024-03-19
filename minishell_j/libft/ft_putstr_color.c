#include "libft.h"

void	ft_putstr_color_fd(int fd, char *s, char *color)
{
	write(fd, color, 7);
	while (*s)
		write(fd, s++, 1);
	write(fd, "\033[0m", 5);
}
