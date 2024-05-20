#include "minishell.h"

char	**dollar_question(t_shell *shell)
{
	char	**new_d_exp;

	new_d_exp = (char **)malloc(sizeof(char *) * 2);
	new_d_exp[0] = ft_itoa(shell->exit_status);
	if (new_d_exp == 0)
		free_all(shell, "Malloc Error\n", 127);
	new_d_exp[1] = NULL;
	return (new_d_exp);
}

char	*quo_dollar_question(t_shell *shell)
{
	char	*new_d_exp;

	new_d_exp = ft_itoa(shell->exit_status);
	if (new_d_exp == 0)
		free_all(shell, "Malloc Error\n", 127);
	return (new_d_exp);
}
