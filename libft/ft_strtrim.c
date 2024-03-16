/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:10:12 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:10:13 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		j;
	char	*ptr;

	j = 0;
	i = 0;
	ptr = NULL;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (in_set(s1[i], set) == 1)
		i++;
	while (len > i && in_set(s1[len - 1], set) == 1)
		len--;
	ptr = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}
