/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:23 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 18:32:45 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_counter(t_token	**tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens + i && tokens[i])
	{
		if (tokens[i]->type == pip)
			count++;
		i++;
	}
	return (count);
}

int	*make_pipe(t_ints *t_int)
{
	int	*pipes;
	int	j;

	pipes = (int *)malloc(sizeof(int) * (t_int->pip_count) * 2);
	if (!pipes)
		return (0);
	j = -1;
	while (++j < t_int->pip_count)
	{
		if (pipe(pipes + 2 * j) < 0)
		{
			perror("");
			return (0);
		}
	}
	return (pipes);
}

void	pipe_end(t_ints *t_int)
{
	int	i;

	i = -1;
	while (++i < (t_int->pip_count) * 2)
		close(t_int->pipes[i]);
}
