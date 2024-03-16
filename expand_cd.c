/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:01:00 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:41:48 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_name(char *line)
{
	int		i;
	char	*var_name;

	i = 1;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	var_name = malloc(sizeof(char) * (i));
	if (!var_name)
		return (0);
	var_name[--i] = '\0';
	while (--i >= 0)
		var_name[i] = line[i + 1];
	return (var_name);
}

char	*get_value(char *var_name, t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp(var_name, ((t_dict *)lst->content)->key))
			return (((t_dict *)lst->content)->value);
		lst = lst->next;
	}
	return (0);
}

int	length_expand(char *line, int type, t_list *lst, t_ints *t_int)
{
	int		i;
	int		s_quote;
	int		d_quote;
	int		len;

	set_index(&i, 0, &s_quote, &d_quote);
	len = ft_strlen(line);
	while (line[++i])
	{
		check_quotes(line[i], &s_quote, &d_quote);
		if ((line[i] == '\'' && !d_quote) || (line[i] == '\"' && !s_quote))
			len--;
		if (in_exit(line[i], line[i + 1], type, s_quote))
		{
			if (exit_length(t_int->e_status, &len))
				return (-1);
		}
		else if (its_quote(line[i], line[i + 1], s_quote, d_quote))
			len--;
		else if (line[i] == '$' && !s_quote && line[i + 1]
			&& has_variable(line[i + 1], line[i + 2], type, lst))
			if (variable_len(&len, &line[i], lst))
				return (-1);
	}
	return (len);
}

char	*expand_line(t_token **token, char *nl, t_list *lst, t_ints *t_int)
{
	t_expand	t;

	set_index(&t.i, &t.j, &t.sq, &t.dq);
	t.l = (*token)->token;
	while (t.l[++t.i])
	{
		check_quotes(t.l[t.i], &t.sq, &t.dq);
		if ((t.l[t.i] == '\'' && !t.dq) || (t.l[t.i] == '\"' && !t.sq))
			continue ;
		if (in_exit(t.l[t.i], t.l[t.i + 1], (*token)->type, t.sq))
		{
			if (exit_begin(&t.i, &t.j, &(nl[t.j]), t_int->e_status))
				return (0);
			continue ;
		}
		if (its_quote(t.l[t.i], t.l[t.i + 1], t.sq, t.dq))
			continue ;
		t.flag = is_var(&t, token, lst, nl);
		if (t.flag == 1)
			return (0);
		if (t.flag == 0)
			(nl)[t.j++] = t.l[t.i];
	}
	(nl)[t.j] = '\0';
	return (nl);
}

char	*expand(t_token **token, t_list *lst, t_ints *t_int)
{
	char	*new_line;
	int		len;

	len = length_expand((*token)->token, (*token)->type, lst, t_int);
	if (len == -1)
		return (0);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (0);
	new_line = expand_line(token, new_line, lst, t_int);
	if (!new_line)
		return (0);
	return (new_line);
}
