/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:09:57 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:09:59 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strndup(const char *s1, char c)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(*s1) * (ft_cstrlen(s1, c) + 1));
	if (!dest)
		return (NULL);
	while (s1[i] != '\0' && i < ft_cstrlen(s1, c))
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
