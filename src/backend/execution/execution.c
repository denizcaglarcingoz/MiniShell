#include "minishell.h"

char	**check_hdoc(t_table table, t_shell *shell)
{
	int		i;
	char	*hdoc;
	char	**hdocs;

	if (table.heredoc[0] == NULL)
		return (NULL);
	i = 0;
	hdoc = NULL;
	while (table.heredoc[i] != NULL)
	{
		if (hdoc != NULL)
			free(hdoc);
		hdoc = hdoc_inp((table.heredoc)[i], shell);
		i++;
	}
	hdocs = (char **)malloc(sizeof(char *) * 2);
	hdocs[0] = hdoc;
	hdocs[1] = NULL;
	return (hdocs);
}

char	*check_in(t_table table)
{
	int	i;

	if (table.in[0] == NULL)
		return (NULL);
	i = 0;
	while (table.in[i] != NULL)
	{
		if (access(table.in[i], F_OK) == -1)
			return (NULL);
		i++;
	}
	return (table.in[i - 1]);
}

void	execution(t_shell *shell)
{
	if (shell->tables == NULL)
		return ;
	if (shell->tables->table_len < 2)
		single_exec(shell);
	else
		pipe_execution(shell);
}
