/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:24 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:13:55 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

int	argument_num(char **args)
{
	int	i;

	i = 0;
	while (args + i && args[i])
		i++;
	return (i);
}

int	check_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg + i && (arg[i] == '-' || arg[i] == '+'))
		i++;
	if (arg + i && arg[i] == '\0')
		return (0);
	while (arg + i && arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all(t_list *env_pack[2], t_cmd_op **cmd, t_ints *t_int)
{
	ft_lstclear_dict(env_pack + 0, free);
	ft_lstclear_dict(env_pack + 1, free);
	free_commands(cmd);
	if (t_int->pipes)
		free(t_int->pipes);
	close(t_int->rlstdin);
	close(t_int->rlstdout);
}

int	exit_shell(t_list *env_pack[2], t_cmd_op **cmd, t_ints *t_int, int is_child)
{
	unsigned long long	tmp;

	tmp = 0;
	if (!is_child)
		ft_putendl_fd("exit", 2);
	if (argument_num(cmd[t_int->counter]->cmd_args) > 2)
	{
		t_int->e_status = error_args("too many arguments",
				cmd[t_int->counter]->cmd_args, 2, 1);
		return (1);
	}
	if (cmd[t_int->counter]->cmd_args + 1 && cmd[t_int->counter]->cmd_args[1])
		tmp = ft_atoi(cmd[t_int->counter]->cmd_args[1]);
	if (cmd[t_int->counter]->cmd_args + 1
		&& (!check_digit(cmd[t_int->counter]->cmd_args[1])
			|| tmp > 9223372036854775808ULL))
		t_int->e_status = error_args("Argument has to be a number",
				cmd[t_int->counter]->cmd_args, 1, 255);
	if (tmp <= 9223372036854775808ULL)
		t_int->e_status = tmp % 256;
	free_all(env_pack, cmd, t_int);
	exit(t_int->e_status);
}
