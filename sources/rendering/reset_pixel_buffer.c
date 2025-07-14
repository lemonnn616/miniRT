/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_pixel_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:19:03 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:21:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			p->colour_sum = new_colour(0, 0, 0);
			p->final_colour = new_colour(0, 0, 0);
			p->ambient = new_colour(0, 0, 0);
			x++;
		}
		y++;
	}
}
