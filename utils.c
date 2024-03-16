/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:55:55 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:08:17 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd_op **cmd, t_list *env_pack[2], t_ints *t_int,
		int is_child)
{
	char	**cmd_arg;

	cmd_arg = cmd[t_int->counter]->cmd_args;
	if (!ft_strcmp(cmd_arg[0], "env"))
		shell_print_env(env_pack + 0, t_int);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		send_build(env_pack + 0, cmd_arg, env_pack + 1, t_int);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		pwd_print(cmd_arg);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		chg_dir(cmd_arg, env_pack + 0, env_pack + 1, t_int);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		t_int->e_status = build_unset(cmd_arg, env_pack + 0, env_pack + 1);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		exit_shell(env_pack, cmd, t_int, is_child);
	else if (!ft_strcmp(cmd_arg[0], "echo"))
		t_int->e_status = echo(cmd_arg);
}

void	create_key_val(t_dict **dict, char *cmd_utils)
{
	t_dict	*tmp;

	tmp = *dict;
	if (ft_strchr(cmd_utils, '='))
		tmp->flag = 1;
	else
		tmp->flag = 0;
	tmp->key = ft_strndup(cmd_utils, '=');
	if (ft_strchr(cmd_utils, '='))
		tmp->value = ft_strdup(ft_strchr(cmd_utils, '=') + 1);
	else
		tmp->value = ft_strdup("");
}

int	open_import(t_cmd_op **cmds, t_ints *t_int, t_token **tokens)
{
	int	infile;

	infile = 0;
	if (cmds[t_int->counter]->redir_in != -2
		&& cmds[t_int->counter]->redir_in != -1)
	{
		if (tokens[cmds[t_int->counter]->redir_in]->type == redir_in)
			infile = open(tokens[cmds[t_int->counter]
					->redir_in + 1]->token, O_RDONLY);
		else if (tokens[cmds[t_int->counter]->redir_in]->type == here_doc)
			infile = heredoc_files(cmds[t_int->counter]->redir_in, 0);
		if (infile < 0)
		{
			perror("");
			return (-1);
		}
	}
	return (infile);
}

int	open_export(t_cmd_op **cmds, t_ints *t_int, t_token **tokens)
{
	int	outfile;

	outfile = 0;
	if (cmds[t_int->counter]->redir_out != -2
		&& cmds[t_int->counter]->redir_out != -1)
	{
		if (tokens[cmds[t_int->counter]->redir_out]->type == redir_out)
			outfile = open(tokens[cmds[t_int->counter]->redir_out + 1]
					->token, O_RDWR | O_CREAT | O_TRUNC, 0000644);
		else if (tokens[cmds[t_int->counter]->redir_out]
			->type == redir_out_append)
			outfile = open(tokens[cmds[t_int->counter]->redir_out + 1]
					->token, O_RDWR | O_CREAT | O_APPEND, 0000644);
		if (outfile < 0)
		{
			perror("");
			return (-1);
		}
	}
	return (outfile);
}
