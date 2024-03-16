/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:55 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:03:16 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_first_t(int *j, int *num, const char *s)
{
	int		d_quote;
	int		s_quote;

	s_quote = 0;
	d_quote = 0;
	while (s[*j] && (s_quote || d_quote
			|| (!its_space(s[*j]) && s[*j] != '|' && !its_redirect(s[*j]))))
	{
		check_quotes(s[*j], &s_quote, &d_quote);
		*j += 1;
		*num += 1;
	}
}

void	read_pip(int *index, int *num, char const *s, t_token **res)
{
	*num = 0;
	(*res)->type = unset;
	while (s[*index] && its_space(s[*index]))
		*index += 1;
	while (s[*index] && !its_space(s[*index]) && s[*index] != '|'
		&& !its_redirect(s[*index]) && s[*index] != '\'' && s[*index] != '\"')
		increment(index, num);
}

void	check_label(int *index, int *num, char const *s, t_token **res)
{
	if (s[*index] == '|')
	{
		increment(index, num);
		(*res)->type = pip;
	}
	else
	{
		while (its_redirect(s[*index]))
			increment(index, num);
		(*res)->type = redirection;
	}
}
