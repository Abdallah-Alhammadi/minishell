/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:47:39 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:30:10 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remake_environment(t_dict *cmd, t_list **env)
{
	t_dict	*new;
	t_list	*node;
	char	*key;
	char	*value;

	key = ft_strdup(cmd->key);
	value = ft_strdup(cmd->value);
	if (key_exists(key, env) == 1)
	{
		if (cmd->flag == 1)
			directory_update(key, value, env);
		return (free(key));
	}
	new = directory_create(key, value, cmd->flag);
	if (!new)
		return (ft_lstclear(env, free));
	node = ft_newdict(new);
	free(new);
	free(key);
	free(value);
	node->next = 0;
	ft_lstadd_back(env, node);
}

int	is_alpha_num(char *cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd, '=');
	if (!tmp || !tmp[0])
		return (1);
	while (tmp[0] + i && tmp[0][i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			free_str_array(tmp);
			return (0);
		}
		i++;
	}
	free_str_array(tmp);
	return (1);
}

int	is_name(char *cmd, char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (arg + i && arg[i] == '\0')
		flag = 0;
	while (arg + i && arg[i])
	{
		if (arg[0] && (ft_isdigit(arg[0])
				|| arg[0] == '='))
		{
			flag = 0;
			break ;
		}
		if (arg && !is_alpha_num(arg))
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

int	send_error(char *cmd, char *arg, t_ints *t_int, int *i)
{
	if (!ft_strcmp(arg, "_") || !ft_strncmp(arg, "_=", 2))
	{
		(*i)++;
		return (1);
	}
	if (!is_name(cmd, arg))
	{
		t_int->e_status = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

void	send_build(t_list **lst, char **cmd_utils, t_list **export,
		t_ints *t_int)
{
	int		i;
	t_dict	*dict;

	i = 1;
	if (!(cmd_utils + i) || !cmd_utils[i])
		return (print_list(export, t_int));
	dict = (t_dict *)malloc(sizeof(t_dict));
	if (!dict)
		return ;
	while (cmd_utils + i && cmd_utils[i])
	{
		if (send_error("export", cmd_utils[i], t_int, &i))
			continue ;
		create_key_val(&dict, cmd_utils[i]);
		if (ft_strchr(cmd_utils[i], '='))
			remake_environment(dict, lst);
		remake_environment(dict, export);
		t_int->e_status = 0;
		directory_free(dict, 1);
		i++;
	}
	free(dict);
}
