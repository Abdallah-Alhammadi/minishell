/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_echo_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:07:01 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:07:20 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_n(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (str + i && str[i] && str[i] == '-')
		i++;
	else
		return (0);
	while (str + i && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **arg)
{
	int	i;

	i = 1;
	if (!(arg + 1) || !arg[1])
	{
		printf("\n");
		return (0);
	}
	while (arg + i && arg[i] && !ft_strncmp(arg[i], "-n", 2) && has_n(arg[i]))
		i++;
	while (arg + i && arg[i])
	{
		printf("%s", arg[i]);
		if (arg + i + 1 && arg[i + 1])
			printf(" ");
		i++;
	}
	if (arg + 1 && arg[1] && !has_n(arg[1]))
		printf("\n");
	return (0);
}

int	check_key(char *cmd, char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (arg + i && arg[i] == '\0')
		flag = 0;
	while (arg + i && arg[i] != '\0')
	{
		if (arg[0] && (ft_isdigit(arg[0])))
		{
			flag = 0;
			break ;
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			flag = 0;
			break ;
		}
		i++;
	}
	if (flag == 0)
		error_message_create(cmd, arg);
	return (flag);
}

int	build_unset(char **cmd_utils, t_list **lst, t_list **export)
{
	int	i;
	int	flag;

	i = 1;
	if (!(cmd_utils + 1) || !cmd_utils[1])
		return (0);
	flag = 0;
	while (cmd_utils + i && cmd_utils[i])
	{
		if (!check_key("unset", cmd_utils[i]))
		{
			flag = 1;
			i++;
			continue ;
		}
		if (key_exists(cmd_utils[i], lst))
			remove_list(lst, cmd_utils[i]);
		if (key_exists(cmd_utils[i], export))
			remove_list(export, cmd_utils[i]);
		flag = 0;
		i++;
	}
	return (flag);
}
