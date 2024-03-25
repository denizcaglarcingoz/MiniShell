#include "libft.h"

int	ft_putstr_color_fd(int fd, char *s, char *color)
{
	int			len;
	const char	*reset_col;

	len = 0;
	reset_col = "\033[0m";
	write(fd, color, ft_strlen(color));
	while (*s)
		len += write(fd, s++, 1);
	write(fd, reset_col, ft_strlen(reset_col));
	return (len);
}
