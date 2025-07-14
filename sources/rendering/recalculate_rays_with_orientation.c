/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_rays_with_orientation.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:18:54 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:35:49 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	recalc_rays_with_orientation(t_data *data)
{
	int			y;
	int			x;
	t_camera	*cam;
	t_vec3		v;
	t_vec3		world;

	cast_rays(data);
	cam = data->scene.active_cam;
	y = 0;
	while (y < data->scene.height)
	{
		x = 0;
		while (x < data->scene.width)
		{
			v = data->pixels[y][x].ray_direction;
			world = vec_add(
					vec_add(
						vec_scale(cam->right, v.x),
						vec_scale(cam->up, v.y)),
					vec_scale(cam->dir, v.z));
			data->pixels[y][x].ray_direction = vec_normalize(world);
			x++;
		}
		y++;
	}
}
