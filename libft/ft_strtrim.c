/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:21:46 by adeslarz          #+#    #+#             */
/*   Updated: 2021/10/20 22:39:58 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set_in_str(char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	char	*str1;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	if (s1 == NULL)
		return (NULL);
	str1 = (char *) s1;
	while (str1[start] && ft_set_in_str(str1[start], set))
		start++;
	end = ft_strlen(str1);
	while (end > start && ft_set_in_str(str1[end - 1], set))
		end--;
	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (dest == NULL)
		return (NULL);
	while (start < end)
		dest[i++] = str1[start++];
	dest[i] = '\0';
	return (dest);
}
