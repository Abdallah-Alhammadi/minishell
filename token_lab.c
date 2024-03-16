/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:05:58 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 18:58:56 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_arg(int index, int begins_w_redir, t_token ***tokens)
{
	(*tokens)[index]->type = file;
	if (begins_w_redir && (*tokens)[index + 1]
		&& (*tokens)[index + 1]->type == unset)
		(*tokens)[index + 1]->type = cmd;
}

int	is_argument(int index, t_token ***tokens)
{
	if (((*tokens)[index]->type == unset
		|| (*tokens)[index]->type == delimiter_q)
		&& sent((*tokens)[index - 1]->type)
		&& (*tokens)[index - 1]->type != here_doc)
		return (1);
	return (0);
}

void	set_token_start(int *index, int *begins_w_redir,
			t_token ***tokens, int flag)
{
	if ((*tokens)[*index]->type == unset)
	{
		(*tokens)[*index]->type = cmd;
		*begins_w_redir = 0;
		if (flag)
			*index += 1;
	}
	else
		*begins_w_redir = 1;
}

void	delimit(int index, int begins_w_redir, t_token ***tokens)
{
	if ((*tokens)[index]->type == unset)
		(*tokens)[index]->type = delimiter;
	if (begins_w_redir && (*tokens)[index + 1]
		&& (*tokens)[index + 1]->type == unset)
		(*tokens)[index + 1]->type = cmd;
}

int	token_lab(t_token ***tokens)
{
	int	i;
	int	begins_w_redir;

	i = 0;
	if ((*tokens)[i] && (*tokens)[i]->type == pip)
		return (1);
	set_token_start(&i, &begins_w_redir, tokens, 1);
	while ((*tokens)[i])
	{
		if (check_syntax(i, tokens))
			return (1);
		if (i > 0 && (*tokens)[i - 1]->type == pip)
			set_token_start(&i, &begins_w_redir, tokens, 0);
		else if ((*tokens)[i]->token[0] == '-')
			(*tokens)[i]->type = option;
		else if (i > 0 && (*tokens)[i - 1]->type == here_doc)
			delimit(i, begins_w_redir, tokens);
		else if (is_argument(i, tokens))
			redirect_arg(i, begins_w_redir, tokens);
		else if ((*tokens)[i]->type == unset)
			(*tokens)[i]->type = arg;
		i++;
	}
	return (0);
}
