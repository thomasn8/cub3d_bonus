/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notblank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:47:32 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:29:54 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_notblank(int c)
{
	if (c > ' ' && c <= '~')
		return (1);
	return (0);
}
