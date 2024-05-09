#include "minishell.h"

char *ft_strjoin_char(char *s1, char c)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	temp = s1;
	s1 = str;
	free(temp);
	return (str);
}

bool str_is_alfa_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_alfa_num(str[i]) && str[i] != '.')
			return (false);
		i++;
	}
	return (true);
}
// special for expansion with . with alfanum

bool is_alfa_num(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}