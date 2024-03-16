/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:06:58 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 20:07:01 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (++i);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	ft_tostr(int nb, char *ptr, int size)
{
	if (nb < 0)
	{
		nb = -nb;
		ptr[0] = '-';
		while (size-- > 1)
		{
			ptr[size] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	else
	{
		while (size-- > 0)
		{
			ptr[size] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	return ;
}

char	*ft_itoa(int n)
{
	char	*ptr;

	if (n == -2147483648)
	{
		ptr = ft_strdup("-2147483648");
		return (ptr);
	}
	ptr = malloc(sizeof(char) * (ft_size(n) + 1));
	if (!ptr)
		return (NULL);
	ft_tostr(n, ptr, ft_size(n));
	ptr[ft_size(n)] = '\0';
	return (ptr);
}
