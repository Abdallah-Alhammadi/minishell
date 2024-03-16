/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:25:28 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:12:26 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	duplicats(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		ft_putstr_fd("duplicates 2: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	return (0);
}

int	start_duplicats(t_cmd_op **cmds, t_ints *t_int, int in, int out)
{
	if (cmds[t_int->counter]->redir_in != -2)
	{
		if (duplicats(in, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmds[t_int->counter]->redir_out != -2)
	{
		if (cmds[t_int->counter]->redir_out == -1)
		{
			if (duplicats(t_int->pipes[1], STDOUT_FILENO) == -1)
				return (-1);
		}
		else
		{
			if (duplicats(out, STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	return (0);
}

int	center_duplicats(t_cmd_op **cmds, t_ints *t_int, int in, int out)
{
	if (cmds[t_int->counter]->redir_in == -1)
	{
		if (duplicats(t_int->pipes[2 * t_int->counter - 2], STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (duplicats(in, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmds[t_int->counter]->redir_out == -1)
	{
		if (duplicats(t_int->pipes[2 * t_int->counter + 1],
				STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (duplicats(out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	end_duplicats(t_cmd_op **cmds, t_ints *t_int, int in, int out)
{
	if (cmds[t_int->counter]->redir_in != -2)
	{
		if (cmds[t_int->counter]->redir_in == -1)
		{
			if (duplicats(t_int->pipes[2 * t_int->counter - 2],
					STDIN_FILENO) == -1)
				return (-1);
		}
		else
		{
			if (duplicats(in, STDIN_FILENO) == -1)
				return (-1);
		}
	}
	if (cmds[t_int->counter]->redir_out != -2)
	{
		if (duplicats(out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	exit_duplicats(t_cmd_op **cmds, t_ints *t_int, t_token **tokens)
{
	int		infile;
	int		outfile;

	infile = open_import(cmds, t_int, tokens);
	outfile = open_export(cmds, t_int, tokens);
	if (infile == -1 || outfile == -1)
		return (-1);
	if (t_int->counter == 0)
	{
		if (start_duplicats(cmds, t_int, infile, outfile) == -1)
			return (-1);
	}
	else if (t_int->counter == t_int->cmd_count - 1)
	{
		if (end_duplicats(cmds, t_int, infile, outfile) == -1)
			return (-1);
	}
	else
		if (center_duplicats(cmds, t_int, infile, outfile) == -1)
			return (-1);
	if (infile > 0)
		close(infile);
	if (outfile > 0)
		close(outfile);
	return (pipe_end(t_int), 0);
}
