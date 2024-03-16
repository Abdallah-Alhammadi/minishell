/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:07:55 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:07:56 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !del)
		return ;
	temp = *lst;
	current = *lst;
	while (current != NULL)
	{
		current = current -> next;
		ft_lstdelone(temp, del);
		temp = current;
	}
	*lst = NULL;
	return ;
}

void	ft_lstclear_dict(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !del)
		return ;
	temp = *lst;
	current = *lst;
	while (current != NULL)
	{
		current = current -> next;
		free(((t_dict *)temp->content)->key);
		free(((t_dict *)temp->content)->value);
		ft_lstdelone(temp, del);
		temp = current;
	}
	*lst = NULL;
	return ;
}
