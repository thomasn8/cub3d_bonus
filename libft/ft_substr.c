/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:03:54 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/20 13:25:35 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		*dest = 0;
		return (dest);
	}
	while (len > 0)
	{
		dest[i++] = s[start++];
		len--;
	}
	dest[i] = '\0';
	return (dest);
}
