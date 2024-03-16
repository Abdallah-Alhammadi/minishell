/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:09:33 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:09:34 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s_len;
	int		ss_len;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1);
	ss_len = ft_strlen(s2);
	ptr = malloc(sizeof(*s1) * (s_len + ss_len + 1));
	if (!ptr)
		return (NULL);
	s_len = 0;
	ss_len = 0;
	while (s1[s_len] != '\0')
	{
		ptr[s_len] = s1[s_len];
		s_len++;
	}
	while (s2[ss_len] != '\0')
		ptr[s_len++] = s2[ss_len++];
	ptr[s_len] = '\0';
	return (ptr);
}
