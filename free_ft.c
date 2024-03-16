/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:09:20 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 18:14:13 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = 0;
	return ;
}

void	free_tokens(t_token ***tokens_p)
{
	int		i;

	i = 0;
	while ((*tokens_p)[i])
	{
		free((*tokens_p)[i]->token);
		free((*tokens_p)[i]);
		i++;
	}
	free((*tokens_p));
}

void	free_commands(t_cmd_op **cmds)
{
	int	i;

	i = 0;
	while (cmds + i && cmds[i])
	{
		free(cmds[i]->cmd);
		free_arr(cmds[i]->cmd_args);
		free(cmds[i]);
		cmds[i] = 0;
		i++;
	}
	if (cmds)
		free(cmds);
	cmds = 0;
}

void	free_environment(t_strs	*cmd_list)
{
	free(cmd_list->env_p);
	cmd_list->env_p = 0;
	free_arr(cmd_list->ind_p);
	cmd_list->ind_p = 0;
	free(cmd_list);
	cmd_list = 0;
}

void	free_child(t_cmd_op **cmds, t_list *env_pack[2], t_ints *t_int,
	t_token **tokens)
{
	free_tokens(&tokens);
	free_commands(cmds);
	ft_lstclear_dict(env_pack + 0, free);
	ft_lstclear_dict(env_pack + 1, free);
	free(t_int->pipes);
}
