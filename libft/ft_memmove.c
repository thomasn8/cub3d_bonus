/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:54:03 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/18 13:46:49 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (dest < s)
		ft_memcpy(dest, src, len);
	else
	{
		while (len--)
			*(unsigned char *)(dst + len) = *(unsigned char *)(s + len);
	}
	return (dest);
}
