#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char *dst;

	dst = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dst);
}

