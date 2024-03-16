/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:25:14 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:42:59 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_ints *t_int)
{
	int	e_status;

	(void)e_status;
	if (waitpid(t_int->child_id, &e_status, 0) == -1)
		return (0);
	if (WIFEXITED(e_status))
		t_int->e_status = WEXITSTATUS(e_status);
	else if (WIFSIGNALED(e_status))
		t_int->e_status = WTERMSIG(e_status) + 128;
	while (waitpid(-1, &e_status, 0) >= 0)
		;
	return (t_int->e_status);
}

int	init_utils(t_token **tokens, t_ints *t_int)
{
	t_int->rlstdin = dup(STDIN_FILENO);
	t_int->rlstdout = dup(STDOUT_FILENO);
	t_int->cmd_count = count_command(tokens);
	t_int->pip_count = pipe_counter(tokens);
	t_int->counter = 0;
	t_int->pipes = 0;
	t_int->child_id = 0;
	if (t_int->pip_count > 0)
	{
		t_int->pipes = make_pipe(t_int);
		if (!t_int->pipes)
			return (-1);
	}
	return (0);
}

int	count_command(t_token	**tokens)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tokens + i && tokens[i])
	{
		if (tokens[i]->type == cmd)
			count++;
		i++;
	}
	return (count);
}

void	reset_fd(t_ints *t_int)
{
	dup2(t_int->rlstdin, STDIN_FILENO);
	close(t_int->rlstdin);
	dup2(t_int->rlstdout, STDOUT_FILENO);
	close(t_int->rlstdout);
}
