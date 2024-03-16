/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:01:06 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 17:56:18 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_index(int *i, int *j, int *s_quote, int *d_quote)
{
	*i = -1;
	if (j)
		*j = 0;
	*s_quote = 0;
	*d_quote = 0;
}

int	its_quote(char c1, char c2, int s_quote, int d_quote)
{
	if (c1 == '$' && !s_quote && !d_quote && (c2 == '\"' || c2 == '\''))
		return (1);
	return (0);
}

int	in_exit(char c1, char c2, int type, int s_quote)
{
	if (c1 == '$' && !s_quote && c2 == '?'
		&& type != delimiter && type != delimiter_q)
		return (1);
	return (0);
}

int	exit_length(int exit_stat, int *len)
{
	char	*var_name;

	var_name = ft_itoa(exit_stat);
	if (!var_name)
		return (1);
	*len -= 2;
	*len += ft_strlen(var_name);
	free(var_name);
	return (0);
}

int	exit_begin(int *i, int *j, char *new_line, int exit_stat)
{
	char	*var_name;

	(void) exit_stat;
	var_name = ft_itoa(g_e_stat);
	if (!var_name)
		return (1);
	ft_memcpy(new_line, var_name, ft_strlen(var_name));
	*i += 1;
	*j += ft_strlen(var_name);
	free(var_name);
	return (0);
}
