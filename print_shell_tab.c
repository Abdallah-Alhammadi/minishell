/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:05:35 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:11:14 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_print_env(t_list **lst, t_ints *t_int)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		printf("%s=%s\n", ((t_dict *)tmp->content)->key,
			((t_dict *)tmp->content)->value);
		tmp = tmp->next;
	}
	t_int->e_status = 0;
}

void	print_list(t_list **lst, t_ints *t_int)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	sort_list(lst);
	tmp = *lst;
	while (tmp)
	{
		if (((t_dict *)tmp->content)->flag == 1)
			printf("initiate -x %s=\"%s\"\n",
				((t_dict *)tmp->content)->key, ((t_dict *)tmp->content)->value);
		else
			printf("initiate -x %s\n", ((t_dict *)tmp->content)->key);
		tmp = tmp->next;
	}
	t_int->e_status = 0;
}
