/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:10:15 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:10:16 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_overload(char *ptr, char const *s)
{
	int	i;

	i = 0;
	ptr = (char *)malloc(sizeof(*s) * 1);
	if (!ptr)
		return (NULL);
	ptr[i] = 0;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*ptr;
	unsigned int	size;

	if (!s)
		return (NULL);
	i = 0;
	ptr = NULL;
	size = ft_strlen(s);
	if (start >= size)
		return ((char *)ft_overload(ptr, s));
	if (len > size - start)
		ptr = (char *)malloc(sizeof(*s) * (size - start + 1));
	else
		ptr = (char *)malloc(sizeof(*s) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start])
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}
