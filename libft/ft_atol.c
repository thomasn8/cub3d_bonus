/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeslarz <adeslarz@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:18:54 by adeslarz          #+#    #+#             */
/*   Updated: 2022/03/03 12:50:47 by adeslarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	sum;

	sum = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sum * sign);
}
