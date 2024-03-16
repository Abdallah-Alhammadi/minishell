/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:47 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:04:19 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char const *s, int index, int s_quote, int d_quote)
{
	if (((its_space(s[index]) || s[index] == '|'
				|| (its_redirect(s[index]) && !its_redirect(s[index + 1])))
			&& s[index + 1] != 0 && !its_space(s[index + 1])
			&& !d_quote && !s_quote) || (((its_redirect(s[index + 1])
					&& !its_redirect(s[index])) || s[index + 1] == '|')
			&& !d_quote && !s_quote))
		return (1);
	return (0);
}

static int	token_nums(char const *s)
{
	int	i;
	int	num;
	int	d_quote;
	int	s_quote;

	num = 1;
	i = 0;
	d_quote = 0;
	s_quote = 0;
	if (!s)
		return (-1);
	while (its_space(s[i]))
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i] != 0)
	{
		check_quotes(s[i], &s_quote, &d_quote);
		if (is_token(s, i, s_quote, d_quote))
			num++;
		i++;
	}
	if (s_quote || d_quote)
		return (-1);
	return (num);
}

int	check_quote(int *j, int num, const char *s, t_token **token)
{
	char	*res;

	res = ft_substr(s, *j - num, num);
	if (!res)
		return (0);
	while (s[*j] && !its_space(s[*j]) && s[*j] != '|' && !its_redirect(s[*j]))
	{
		num = 0;
		read_first_t(j, &num, s);
		if (num)
		{
			res = join_free(res, ft_substr(s, *j - num, num));
			if (!res)
				return (0);
			continue ;
		}
		*j += 1;
	}
	(*token)->token = res;
	return (*j);
}

t_token	**split_tokens(char const *s, t_token ***res)
{
	int	i;
	int	j;
	int	num;

	i = -1;
	j = 0;
	while (++i < token_nums(s))
	{
		read_pip(&j, &num, s, &(*res)[i]);
		if (s[j] == '\'' || s[j] == '\"')
		{
			if (!check_quote(&j, num, s, (&(*res)[i])))
				return (malloc_error(*res, i));
			if (i > 0 && (*res)[i - 1] && (*res)[i - 1]->type == redirection)
				(*res)[i]->type = delimiter_q;
			continue ;
		}
		if (!num && (s[j] == '|' || its_redirect(s[j])))
			check_label(&j, &num, s, &((*res)[i]));
		(*res)[i]->token = ft_substr(s, j - num, num);
		if ((*res)[i]->token == NULL)
			return (malloc_error(*res, i));
	}
	(*res)[i] = NULL;
	return (*res);
}

t_token	**start_tokens(char const *line)
{
	t_token	**res;
	int		count;
	int		i;

	count = token_nums(line);
	if (count == -1)
		return (NULL);
	if (!count)
		return (empty_token());
	res = malloc(sizeof(t_token *) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = malloc(sizeof(t_token));
		if (!res[i])
			return (malloc_error(res, i));
		i++;
	}
	split_tokens(line, &res);
	return (res);
}
