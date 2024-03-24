#include "libft.h"

void	ft_putstr_color_fd(int fd, char *s, char *color)
{
	const char *reset_col;
	
	reset_col = "\033[0m";
	write(fd, color, ft_strlen(color));
	while (*s)
		write(fd, s++, 1);
	write(fd, reset_col, ft_strlen(reset_col));
}
