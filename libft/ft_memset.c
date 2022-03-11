/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:58:02 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/14 14:58:10 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned char	*p;

	p = (unsigned char *) b;
	while (len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return (b);
}
