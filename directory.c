/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:25:21 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 17:30:35 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

t_dict	*directory_create(char *key, char *value, int flag)
{
	t_dict	*new;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	if (flag == 1)
		new->flag = 1;
	else
		new->flag = 0;
	return (new);
}

int	directory_update(char *key, char *value, t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(key, ((t_dict *)tmp->content)->key))
		{
			free(((t_dict *)tmp->content)->value);
			((t_dict *)tmp->content)->value = value;
			((t_dict *)tmp->content)->flag = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	directory_free(t_dict	*dict, int flag)
{
	free(dict->key);
	dict->key = 0;
	free(dict->value);
	dict->value = 0;
	if (!flag)
		free(dict);
	dict = 0;
}

int	key_exists(char *s, t_list **new)
{
	t_list	*tmp;

	tmp = *new;
	while (tmp)
	{
		if (ft_strcmp(s, ((t_dict *)tmp->content)->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_val(t_list **lst, char *key)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(key, ((t_dict *)tmp->content)->key))
			return (((t_dict *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (0);
}
