/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:05:53 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 18:20:32 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	send_label(t_token *token)
{
	if (!ft_strcmp(token->token, "<"))
		token->type = redir_in;
	if (!ft_strcmp(token->token, ">"))
		token->type = redir_out;
	if (!ft_strcmp(token->token, "<<"))
		token->type = here_doc;
	if (!ft_strcmp(token->token, ">>"))
		token->type = redir_out_append;
	if (token->type == redirection)
		return (1);
	return (0);
}

int	check_syntax(int index, t_token ***tokens)
{
	if (((*tokens)[index]->type == pip && ((*tokens)[index - 1]->type == pip
		|| !(*tokens)[index + 1])) || ((*tokens)[index]->type == redirection
			&& send_label((*tokens)[index]))
			|| (sent((*tokens)[index]->type) && (!(*tokens)[index + 1]
			|| !((*tokens)[index + 1]->type == unset
			|| (*tokens)[index + 1]->type == delimiter_q)
			|| ((*tokens)[index]->type != here_doc
			&& !valid_file((*tokens)[index + 1]->token)))))
		return (1);
	return (0);
}

int	sent(enum e_input_type type)
{
	if (type == redir_in || type == redir_out || type == here_doc
		|| type == redir_out_append)
		return (1);
	return (0);
}

int	valid_file(char *name)
{
	if (name[0] == '/' || name[0] == '.' || name[0] == ':')
		return (0);
	return (1);
}
