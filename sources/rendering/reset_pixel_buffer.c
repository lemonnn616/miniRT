/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_pixel_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:19:03 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:24 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

void	reset_pixel_buffer(t_data *d)
{
	int		y;
	int		x;
	t_pixel	*p;

	y = 0;
	while (y < d->scene.height)
	{
		x = 0;
		while (x < d->scene.width)
		{
			p = &d->pixels[y][x];
			p->color_sum = new_color(0, 0, 0);
			p->final_color = new_color(0, 0, 0);
			p->ambient = new_color(0, 0, 0);
			p->spp = 0;
			x++;
		}
		y++;
	}
}
