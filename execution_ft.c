/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:12 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 18:38:46 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_find(t_token **tokens, int i)
{
	while (tokens + i && tokens[i] && tokens[i]->type != pip)
	{
		if (tokens[i]->type == cmd)
			return (i);
		i++;
	}
	return (-1);
}

void	counter_update(t_ints *t_int)
{
	t_int->e_status = 1;
	t_int->counter++;
}

int	redirect(t_token **tokens, t_ints *t_int, int i)
{
	while (tokens + i && tokens[i] && tokens[i]->type != pip)
	{
		if (tokens[i]->type == redir_in)
		{
			if (error_checker_rin(tokens, i, 0, t_int) == -1)
				return (-5);
		}
		else if (tokens[i]->type == here_doc)
		{
			if (error_hd_checker(tokens, i, 0, t_int) == -1)
				return (-5);
		}
		else if (tokens[i]->type == redir_out)
		{
			if (check_rout(tokens, i, 0, t_int) == -1)
				return (-5);
		}
		else if (tokens[i]->type == redir_out_append)
		{
			if (shell_out_checker(tokens, i, 0, t_int) == -1)
				return (-5);
		}
		i++;
	}
	return (0);
}

int	next_pipe(t_token **tokens, int i)
{
	int	j;

	j = i;
	while (tokens + j && tokens[j])
	{
		if (tokens[j]->type != pip)
			j++;
		else
			break ;
	}
	if (tokens + j && tokens[j] && tokens[j]->type == pip)
		j++;
	return (j);
}
