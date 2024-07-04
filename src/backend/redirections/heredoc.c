/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:53:53 by dcingoz           #+#    #+#             */
/*   Updated: 2024/07/04 22:02:37 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hdoc_strjoin(char *s1, char *s2, size_t s2_len, t_shell *shell)
{
	size_t	s1_len;
	char	*join;

	if (!s2)
		return (NULL);
	if (!s1 && s2)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	join = (char *)malloc((s1_len + s2_len + 2) * sizeof(char));
	if (!join)
	{
		if (s1 != NULL)
			free(s1);
		free_all(shell, "Malloc Error\n", 127);
	}
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	join[s1_len + s2_len] = '\n';
	join[s1_len + s2_len + 1] = '\0';
	if (s1 != NULL)
		free(s1);
	return (join);
}

int	hdoc_check(char **input, char *whole_inp, t_shell *shell)
{
	if (g_sig_int == SIGUSR1)
	{
		if (whole_inp != NULL)
			free(whole_inp);
		shell->pipe_hdoc_sig = 1;
		return (1);
	}
	errno = 0;
	*input = readline(">");
	if (errno != 0)
	{
		if (*input != 0)
			free(*input);
		free_all(shell, "readline malloc", 127);
	}
	return (0);
}

char	*hdoc_inp(char *h_name, t_shell *shell)
{
	char	*input;
	char	*whole_inp;

	signal(SIGINT, sigint_handler_hdoc);
	errno = 0;
	whole_inp = NULL;
	while (1)
	{
		if (hdoc_check(&input, whole_inp, shell))
			return (NULL);
		if (input == NULL)
			break ;
		if (ft_strncmp(input, h_name, ft_strlen(h_name)) == 0 \
		&& ft_strlen(h_name) == ft_strlen(input))
			break ;
		else
		{
			whole_inp = hdoc_strjoin(whole_inp, input, \
			ft_strlen(input), shell);
			if (whole_inp == NULL)
				return (free(input), NULL);
		}
		free(input);
	}
	return (free(input), whole_inp);
}

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
	if (!hdocs)
	{
		free(hdoc);
		free_all(shell, "hdocs malloc error", 127);
	}
	hdocs[0] = hdoc;
	hdocs[1] = NULL;
	return (hdocs);
}

char	*check_hdoc_p(t_table table, t_shell *shell)
{
	int		i;
	char	*hdoc;

	i = 0;
	hdoc = NULL;
	while (table.heredoc[i] != NULL)
	{
		if (hdoc != NULL)
			free(hdoc);
		hdoc = hdoc_inp((table.heredoc)[i], shell);
		if (g_sig_int == SIGUSR1)
			return (NULL);
		i++;
	}
	return (hdoc);
}
