/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:13:02 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/20 15:56:11 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) src;
	str2 = (unsigned char *) dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (dest);
}
