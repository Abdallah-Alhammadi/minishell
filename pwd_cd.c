/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:25:05 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:40:07 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recive_pwd(char **cmd_utils)
{
	char	*cwd;

	cwd = 0;
	cwd = getcwd(cwd, 0);
	if (!cwd)
	{
		ft_putstr_fd("N&A: ", 2);
		ft_putstr_fd(cmd_utils[0], 2);
		ft_putstr_fd(": ", 2);
		if (cmd_utils + 1 && cmd_utils[1])
		{
			ft_putstr_fd(cmd_utils[1], 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	return (cwd);
}

void	pwd_print(char **cmd_utils)
{
	char	*tmp;

	tmp = recive_pwd(cmd_utils);
	if (!tmp)
		return ;
	printf("%s\n", tmp);
	free(tmp);
}

int	go_home(char **cmd_utils, t_list **lst, t_ints *t_int)
{
	if (cmd_utils + 1 && cmd_utils[1] == 0)
	{
		if (key_exists("HOME", lst))
		{
			if (chdir(get_val(lst, "HOME")) == -1)
			{
				ft_putstr_fd("N&A: cd: ", 2);
				ft_putstr_fd(get_val(lst, "HOME"), 2);
				ft_putendl_fd(":Directory does not exist", 2);
				t_int->e_status = 1;
				return (1);
			}
		}
		else
		{
			t_int->e_status = 1;
			ft_putendl_fd("N&A: cd: HOME not set", 2);
			return (-1);
		}
		return (0);
	}
	return (0);
}

void	remake_env_free(t_dict *dict, t_list **lst, t_list **export, int flag)
{
	dict->flag = 1;
	if (flag == 0)
	{
		remake_environment(dict, lst);
		remake_environment(dict, export);
		if (dict->key)
			free(dict->key);
		if (dict->value)
			free(dict->value);
		return ;
	}
	remake_environment(dict, lst);
	remake_environment(dict, export);
	if (dict->key)
		free(dict->key);
	if (dict->value)
		free(dict->value);
}

int	chg_dir(char **cmd_utils, t_list **lst, t_list **export, t_ints *t_int)
{
	char	*val;
	t_dict	*dict;

	if (go_home(cmd_utils, lst, t_int) == -1)
		return (0);
	else if (cmd_utils + 1 && cmd_utils[1] && chdir(cmd_utils[1]) == -1)
	{
		t_int->e_status = error_args(strerror(errno), cmd_utils, 1, 1);
		return (1);
	}
	val = recive_pwd(cmd_utils);
	if (!val)
		return (1);
	dict = (t_dict *)malloc(sizeof(t_dict));
	if (!dict)
		return (error_args(strerror(errno), 0, 0, 1), 1);
	dict->key = ft_strdup("OLDPWD");
	dict->value = ft_strdup(get_val(lst, "PWD"));
	remake_env_free(dict, lst, export, 1);
	dict->key = ft_strdup("PWD");
	dict->value = ft_strdup(val);
	remake_env_free(dict, lst, export, 0);
	free(dict);
	return (free(val), 0);
}
