/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcingoz <dcingoz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:21 by dcingoz           #+#    #+#             */
/*   Updated: 2024/06/14 16:31:39 by dcingoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	init_loop(char **content, int d_quo_qty, int quo_qty, int i)
{
	// ft_putstr_fd("content: -", 1);
	// ft_putstr_fd(*content, 1);
	// ft_putchar_fd('-', 1);
	// ft_putchar_fd('\n', 1);
	int first_quo = 0;

	while (1)
	{
		if ((*content)[i] == '\0')
			break ;
		if ((*content)[i] == '"')
		{
			if (first_quo == 0)
				first_quo = 1;
			d_quo_qty++;
			// if (d_quo_qty == 2)
			// {
			// 	d_quo_qty = 0;
			// 	// if (quo_qty % 2 == 1)
			// 	// {	
			// 	// write(1, "BBBBBBBaa\n", 11);
			// 	// 	quo_qty = 0;
			// 	// }
			// }
		}
		if ((*content)[i] == '\'')
		{		
			if (first_quo == 0)
				first_quo = 2;	
			quo_qty++;
			// if (quo_qty == 2)
			// {
			// 	quo_qty = 0;
			// }
			// ft_putstr_fd("IN quo_qty: ", 1);
			// ft_putnbr_fd(quo_qty, 1);
			// ft_putstr_fd("\n", 1);
		}
		if (is_white_space((*content)[i]) == true)
		{	
			// ft_putstr_fd("contentchar: a", 1);
			// ft_putchar_fd((*content)[i], 1);
			// ft_putstr_fd("a\n", 1);
			// ft_putstr_fd("Break d_quo_qty: ", 1);
			// ft_putnbr_fd(d_quo_qty, 1);
			// ft_putstr_fd("\n", 1);
			// ft_putstr_fd("Break quo_qty: ", 1);
			// ft_putnbr_fd(quo_qty, 1);
			// ft_putstr_fd("\n", 1);
			// ft_putstr_fd("Break first_quo: ", 1);
			// ft_putnbr_fd(first_quo, 1);
			// ft_putstr_fd("\n", 1);
			if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
				break ;
			if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
				break ;
			if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
				break ;
		}
		if (((*content)[i] == '\'' || (*content)[i] == '"') && (content[0][i + 1] == '\0' || is_white_space(content[0][i + 1]) == true))
		{
			
			i++;
			if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
				break ;
			if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
				break ;
			if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
				break ;
		}
		
		if (is_meta_char((*content)[i]) == true)
		{	
			// ft_putstr_fd("contentchar: a", 1);
			// ft_putchar_fd((*content)[i], 1);
			// ft_putstr_fd("a\n", 1);
			// ft_putstr_fd("Meta d_quo_qty: ", 1);
			// ft_putnbr_fd(d_quo_qty, 1);
			// ft_putstr_fd("\n", 1);
			// ft_putstr_fd("Meta quo_qty: ", 1);
			// ft_putnbr_fd(quo_qty, 1);
			// ft_putstr_fd("\n", 1);
			// ft_putstr_fd("Meta first_quo: ", 1);
			// ft_putnbr_fd(first_quo, 1);
			// ft_putstr_fd("\n", 1);
			if (first_quo == 2 && quo_qty % 2 == 0 && quo_qty != 0)
				break ;
			if (first_quo == 1 && d_quo_qty % 2 == 0 && d_quo_qty != 0)
				break ;
			if (first_quo == 0 && d_quo_qty % 2 == 0 && quo_qty % 2 == 0)
				break ;
			// write(1, "BBBBBBB\n", 8);
		} 
		i++;
	}
	return (i);
}

t_tokens	*token_init_string(t_tokens *c_token, char **content, \
t_token_type type)
{
	t_tokens	*new_token;
	int			i;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	if (c_token != NULL)
		c_token->next = new_token;
	i = init_loop(content, 0, 0, 0);
	new_token->content = (char *)malloc(i + 1);
	if (new_token->content == NULL)
		return (NULL);
	ft_strlcpy(new_token->content, *content, i + 1);
	while (i > 0)
	{
		(*content)++;
		i--;
	}
	(*content)--;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}
