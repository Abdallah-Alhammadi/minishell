/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:51 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 19:02:03 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment(int *num1, int *num2)
{
	*num1 += 1;
	*num2 += 1;
}

char	*join_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

t_token	**malloc_error(t_token **res, int i)
{
	i--;
	if (i >= 0)
	{
		free(res[i]);
		i--;
	}
	while (i >= 0)
	{
		free(res[i]->token);
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

t_token	**empty_token(void)
{
	t_token	**res;

	res = malloc(sizeof(t_token *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	return (res);
}
