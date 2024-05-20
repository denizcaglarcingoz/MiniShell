/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:53:53 by dcingoz           #+#    #+#             */
/*   Updated: 2024/05/13 22:37:34 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t g_sig_int;
//basic implementation of heredoc
// after returned the string
// complexcases such as  cat << "EOF" or cat << 'EOF' or  
// cat << EOF
// >$HOME
// >EOF
// shold be handled

char	*hdoc_strjoin(char *s1, char *s2, size_t s2_len)
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
		return (perror("Malloc Error\n"), NULL);
	}
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	join[s1_len + s2_len] = '\n';
	join[s1_len + s2_len + 1] = '\0';
	if (s1 != NULL)
		free(s1);
	return (join);
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
		if (g_sig_int == 1)
		{
			if (whole_inp != NULL)
				free(whole_inp);
			free_all(shell, "no print", 0);
			return (NULL);
		}
		if ((input = readline(">")) == NULL)
		{
			perror("readline malloc");
			if (input != 0)
				free(input);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(input, h_name, ft_strlen(h_name)) == 0 && ft_strlen(h_name) == ft_strlen(input)) 
			break ;
		else
		{
			if ((whole_inp = hdoc_strjoin(whole_inp, input, ft_strlen(input))) == NULL)
				return (free(input), NULL);
		}
		free(input);
	}
	return(free(input), whole_inp);
}

// TEST

// int main (int argc, char **argv)
// {
// 	char *h_name = argv[1];
// 	char *input;
// 	input = hdoc_inp(h_name);
// 	printf("\n\nHEREDOC:\n%s", input);
// 	free(input);
// 	return (0);
// }
