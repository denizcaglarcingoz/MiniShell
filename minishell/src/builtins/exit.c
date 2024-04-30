#include "minishell.h"

int	is_all_digit(char *s)
{
	int	i;
	
	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	check_args(char **full_cmd)
{
	if (ft_matrix_len(full_cmd) > 2)
	{
		ft_putstr_color_fd(2, "minishell: exit: too many arguments\n", RED);
		return (1);
	}
	return (0);
}

void	final_free(t_table *table, t_shell *shell)
{
	clear_history();
	free(shell->input);
	free_all_env(shell->env);
	free_all_env(shell->exported);
	if (table)
		free_t_content_alloc_and_table(table, shell->table_len);
}

int	ft_exit(t_table *table, char **full_cmd, t_shell *shell)
{
	long int code;

	ft_putstr_color_fd(1, "Exiting MINISHELL!\n", BOLD_GREEN);
	if (check_args(full_cmd))
		code = 1;
	else if (full_cmd[1])
	{
		if (!is_all_digit(full_cmd[1]))
		{
				ft_putstr_color_fd(2, "minishell: exit: ", RED);
				ft_putstr_color_fd(2,  full_cmd[1], RED);
				ft_putstr_color_fd(2, ": numeric argument required\n", RED);
				code = 2;
		}
		else
		{
			code = (ft_atol(full_cmd[1]) % 256);
			if (code < 0)
				code += 256; 
		}
	}
	else
		code = 0;
	final_free(table, shell);
	printf("exit code: %d\n", code);//-------------
	exit(code);
	return (code);
}