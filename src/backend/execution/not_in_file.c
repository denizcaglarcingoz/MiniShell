/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_in_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:14:55 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/18 12:07:22 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	not_in_out(char *in, t_shell *shell)
{
	t_tokens	*first;

	first = shell->tokens;
	while (shell->tokens)
	{
		if (shell->tokens->type == 5 || shell->tokens->type == 7)
		{
			shell->tokens = shell->tokens->next;
			output_file(shell->tokens->content, NULL);
		}
		if (shell->tokens->type == 4)
		{
			shell->tokens = shell->tokens->next;
			if (ft_strcmp(shell->tokens->content, in) == 0)
				break ;
		}
		shell->tokens = shell->tokens->next;
	}
	shell->tokens = first;
}

void	not_in_out_p(char *in, t_shell *shell, int table_num)
{
	while (shell->tokens)
	{
		if (shell->tokens->type == PIPE)
			table_num--;
		if (table_num == 0)
			break ;
		shell->tokens = shell->tokens->next;
	}
	while (shell->tokens)
	{
		if (shell->tokens->type == 5 || shell->tokens->type == 7)
		{
			shell->tokens = shell->tokens->next;
			output_file(shell->tokens->content, NULL);
		}
		if (shell->tokens->type == 4)
		{
			shell->tokens = shell->tokens->next;
			if (ft_strcmp(shell->tokens->content, in) == 0)
				break ;
		}
		shell->tokens = shell->tokens->next;
	}
}

void	not_in_file_p(char **in, t_shell *shell, int table_num)
{
	int			i;
	t_tokens	*first;

	i = 0;
	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break ;
		i++;
	}
	first = shell->tokens;
	if (shell->tables[table_num].out[0] != NULL)
		not_in_out_p(in[i], shell, table_num);
	shell->tokens = first;
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 1);
}

void	not_in_file(char **in, t_shell *shell)
{
	int	i;

	i = 0;
	while (in[i] != NULL)
	{
		if (access(in[i], F_OK) == -1)
			break ;
		i++;
	}
	if (shell->tables[0].out[0] != NULL)
		not_in_out(in[i], shell);
	write(1, "", 0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(in[i], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all(shell, "no print", 0);
	shell->exit_status = 1;
}
