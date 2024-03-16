/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:25:10 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:14:28 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_strdin1(t_token	**tokens, int j)
{
	if (tokens[j]->type == redir_in || tokens[j]->type == here_doc)
		return (j);
	return (-2);
}

int	check_strdin(t_token	**tokens, int i)
{
	int	j;

	j = n_pip_command(tokens, i);
	if (tokens[j] == 0 || tokens[j]->type == pip || tokens[j]->type == cmd)
		j--;
	while (j > i)
	{
		if (tokens[j]->type == redir_in || tokens[j]->type == here_doc)
			return (check_strdin1(tokens, j));
		j--;
	}
	j = --i;
	while (j >= 0 && tokens + j && tokens[j] && tokens[j]->type != cmd)
	{
		if (tokens[j]->type == redir_in || tokens[j]->type == here_doc)
			return (check_strdin1(tokens, j));
		else if (tokens[j]->type == pip)
			return (-1);
		j--;
	}
	return (-2);
}

int	check_stdout(t_token	**tokens, int i)
{
	int	j;

	j = n_pip_command(tokens, i);
	if (tokens[j] == 0 || tokens[j]->type == pip || tokens[j]->type == cmd)
		j--;
	while (j > i)
	{
		if (tokens[j]->type == redir_out || tokens[j]->type == redir_out_append)
			return (j);
		j--;
	}
	j = i - 1;
	while (j >= 0 && tokens + j && tokens[j] && tokens[j]->type != cmd
		&& tokens[j]->type != pip)
	{
		if (tokens[j]->type == redir_out || tokens[j]->type == redir_out_append)
			return (j);
		j--;
	}
	j = n_pip_command(tokens, i);
	if (tokens[j] != 0 && tokens[j]->type == pip)
		return (-1);
	return (-2);
}

t_cmd_op	*create_command(t_strs **cmd_list, t_token **tokens,
	t_cmd_op **cmds, int i)
{
	t_cmd_op	*command;

	command = (t_cmd_op *)malloc((sizeof(t_cmd_op)));
	if (!command)
	{
		ft_putendl_fd("Malloc error-list", 2);
		free_commands(cmds);
		return (0);
	}
	command->redir_in = check_strdin(tokens, i);
	command->redir_out = check_stdout(tokens, i);
	command->cmd_args = cmd_arguments(tokens, &i);
	if (command->cmd_args + 0 && is_builtin(command->cmd_args[0]))
		command->cmd = ft_strdup(command->cmd_args[0]);
	else if (command->cmd_args[0] == 0 || !ft_strcmp(command->cmd_args[0], ""))
		command->cmd = ft_strdup("");
	else if ((ft_strchr(command->cmd_args[0], '/'))
		|| (command->cmd_args[0] && !(*cmd_list)->env_p))
		command->cmd = ft_strdup(command->cmd_args[0]);
	else if ((*cmd_list)->env_p)
		command->cmd = commant_path((*cmd_list)->ind_p,
				tokens[i]->token);
	return (command);
}

t_cmd_op	**create_commands(t_strs **cmd_list, t_token **tokens)
{
	int			i;
	int			j;
	t_cmd_op	**cmds;

	i = 0;
	j = 0;
	cmds = (t_cmd_op **)malloc(sizeof(t_cmd_op *) * ((*cmd_list)->cmd_len + 1));
	if (!cmds)
	{
		ft_putendl_fd("Malloc error-list", 2);
		return (0);
	}
	while (tokens + i && tokens[i])
	{
		if (tokens[i]->type == cmd)
		{
			cmds[j] = create_command(cmd_list, tokens, cmds, i);
			if (!cmds[j++])
				return (0);
		}
		i++;
	}
	cmds[j] = 0;
	return (cmds);
}
