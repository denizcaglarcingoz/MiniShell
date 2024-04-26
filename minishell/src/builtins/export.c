#include "minishell.h"

//export by itself gives list of exported vars.


/* int	has_equal(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
} */

/* void	handle_assign(char *str)
{
	char	*varname;
	char	*varval;
	int		name_len;
	int		var_len;
	int		i;

	name_len = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	while (str[++i])
	{
		if (is_white_space(str[i]))
			i++;
		else
			name_len++;
	}
	varval = (char *)malloc((name_len + 1) * sizeof(char));
	ft_strlcpy(varname, str, name_len);
	printf("%s\n", varname);
	free (varname);
	

} */
int	check_valid_id(char *s)
{
	int	i;

	i = 0;	
	if (ft_isdigit(s[i]) || !(s[i] == '_' || !ft_isalpha(s[i])))
		return (1);
	while (s[++i] && s[++i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (1);
	}
	return (0);
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	if (env == NULL)
	{
		printf("Empty Exported Variable List\n");
		return ;
	}
	while (env[++i] != NULL)
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j] != '=')
			ft_putchar_fd(env[i][j], 1);
		ft_putchar_fd(env[i][j], 1);
		ft_putstr_fd("\"", 1);
		while (env[i][++j])
			ft_putchar_fd(env[i][j], 1);
		ft_putstr_fd("\"\n", 1);
	}
}

int	invalid_id(char *id)
{
	ft_putstr_color_fd(2, "minishell: export: '", RED);
	ft_putstr_color_fd(2, id, RED);
	ft_putstr_color_fd(2, "': not a valid identifier\n", RED);
	return (1);
}

int	ft_export(char **full_cmd, t_shell *shell)
{
	//char	*var;
	int		i;
	int		status;

	status = 0;
	if (!(*(full_cmd + 1)))
		print_export(shell->exported);//works now!
	else
	{
		i = 0;
		while (full_cmd[++i])
		{
			if (!check_valid_id(full_cmd[i]))
				status = invalid_id(full_cmd[i]);
			else
			{	
				shell->env = add_env(shell->env, full_cmd[i]);//return_val	
				shell->exported = add_env(shell->exported, full_cmd[i]);//return value...
				//print_env(shell->exported);

			}		
		}
			/* else if (has_equal(full_cmd[1]))
				handle_assign(full_cmd[1]); */
				//add_env(shell->exported, var);		
		//send to expander after equal
		//check var!
		//var = remove_quotes(tokens->content);		
	}
	return (status);
}