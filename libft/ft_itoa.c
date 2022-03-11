/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:23:05 by adeslarz          #+#    #+#             */
/*   Updated: 2022/02/21 10:57:42 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_len_nbr(int nbr)
{
	int		size;

	size = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		size++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa_2(int nbr)
{
	char	*dest;
	int		size;

	size = ft_len_nbr(nbr);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	if (nbr < 0)
	{
		dest[0] = '-';
		nbr = nbr * -1;
	}
	dest[size] = '\0';
	while (nbr > 0)
	{
		size--;
		dest[size] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (dest);
}

char	*min_int(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*int_is_zero(char *dest)
{
	int	i;

	i = 0;
	dest[i] = '0';
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_itoa(int nbr)
{
	char	*dest;

	if (nbr == -2147483648)
	{
		dest = malloc(sizeof(char) * 12);
		if (!dest)
			return (NULL);
		dest = min_int(dest, "-2147483648");
		return (dest);
	}
	if (nbr == 0)
	{
		dest = malloc(2);
		dest = int_is_zero(dest);
		return (dest);
	}
	dest = ft_itoa_2(nbr);
	return (dest);
}
