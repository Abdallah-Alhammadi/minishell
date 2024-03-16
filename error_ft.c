/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:03 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:58:39 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message_create(char *cmd, char *arg)
{
	ft_putstr_fd("N&A: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': invalid identifier", 2);
}

int	error_args(char *msg, char **args, int num, int err)
{
	ft_putstr_fd("Yash: ", 2);
	if ((num == 1 || num == 2) && args + 0 && args[0])
		ft_putstr_fd(args[0], 2);
	if (args + 1 && args[1] && num != 2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(args[1], 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (err);
}

void	exit_error(t_cmd_op *cmd, char **args, t_ints *t_int)
{
	DIR	*dir;

	dir = opendir(cmd->cmd);
	if (dir)
	{
		t_int->e_status = error_args("is a directory", args, 2, 126);
		closedir(dir);
	}
	else if (ft_strchr(cmd->cmd, '/')
		&& access(cmd->cmd, F_OK) != 0)
		t_int->e_status = error_args("Directory does not exist", args, 2, 127);
	else if (ft_strchr(cmd->cmd, '/') && access(cmd->cmd, X_OK) != 0
		&& access(cmd->cmd, F_OK) == 0)
		t_int->e_status = error_args("No permissions", args, 2, 126);
	else if (access(cmd->cmd, X_OK) == 0 && ft_strchr(cmd->cmd, '/'))
		return ;
	else
		t_int->e_status = error_args("command not found", args, 2, 127);
}
