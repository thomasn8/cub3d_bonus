/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:16:01 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/14 15:22:12 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	int				i;

	i = 0;
	str = (unsigned char *) s;
	while (n > 0)
	{
		if (str[i] == (unsigned char) c)
			return (&str[i]);
		i++;
		n--;
	}
	return (NULL);
}
