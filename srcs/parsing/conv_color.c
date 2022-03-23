/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:41:58 by desa              #+#    #+#             */
/*   Updated: 2022/03/23 16:42:00 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned long	create_rgb(int t, int r, int g, int b)
{
	return (((t & 0xFF) << 24) + ((r & 0xFF) << 16) + \
			((g & 0xFF) << 8) + (b & 0xFF));
}

void	get_color(int nbr, int sum, t_parse *parse, char c)
{
	if (nbr == 1)
		parse->r = sum;
	else if (nbr == 2)
		parse->g = sum;
	else if (nbr == 3)
		parse->b = sum;
	if (parse->r != -1 && parse->g != -1 && parse->b != -1 && c == 'F')
		parse->hex_f = create_rgb(0, parse->r, parse->g, parse->b);
	else if (parse->r != -1 && parse->g != -1 && parse->b != -1 && c == 'S')
		parse->hex_s = create_rgb(0, parse->r, parse->g, parse->b);
}
