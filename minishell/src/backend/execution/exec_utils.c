#include "minishell.h"

t_tokens *start_of_pipe(t_tokens *tokens, int table_id)
{
	int i;
	t_tokens *tmp;

	tmp = tokens;
	i = 0;
	while (i < table_id)
	{
		while (tmp->type != PIPE && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->type == PIPE)
		{	
			i++;
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			break;
	}
	return (tmp);
}

char *read_file(int fd)
{
	char buffer[BUFFER_SIZE];
	int count_read;
	char *read_str;

	read_str = ft_strdup("");
	while ((count_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[count_read] = '\0';
		read_str = ft_strjoin(read_str, buffer);
		// protect this
	}
	printf("inside read_file\n");
	return (read_str);
}

int	is_builtin(char *cmd)
{
	int i;

	i = 0;
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0) 
		i++;
	else if (ft_strcmp(cmd, "echo") == 0)
		i++;
	else if (ft_strcmp(cmd, "cd") == 0) 
		i++;
	else if (ft_strcmp(cmd, "pwd") == 0) 
		i++;
	return (i);
}

char *last_str(char **strs)
{
	int i;

	i = 0;
	if (strs[0] == NULL)
		return (NULL);
	while (strs[i] != NULL)
			i++;
	return (strs[i - 1]);
}
