/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:09:11 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:39:35 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_free(t_dict *dict)
{
	char	*new;
	char	*tmp;

	tmp = ft_strdup(dict->key);
	new = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(new, dict->value);
	free(new);
	return (tmp);
}

char	**make_environments_vars(t_list **lst)
{
	t_list	*tmp;
	int		size;
	char	**envp;
	int		i;

	tmp = *lst;
	size = ft_lstsize(tmp);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!envp)
		return (0);
	while (tmp)
	{
		envp[i] = ft_join_free((t_dict *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}

void	make_environment(t_list **head, char **envp)
{
	int		i;
	t_list	*new;
	t_dict	*dict;

	i = -1;
	while (envp[++i])
	{
		dict = directory_create(ft_strndup(envp[i], '='),
				ft_strdup(ft_strchr(envp[i], '=') + 1), 1);
		new = ft_newdict(dict);
		ft_lstadd_back(head, new);
		directory_free(dict, 0);
	}
}
