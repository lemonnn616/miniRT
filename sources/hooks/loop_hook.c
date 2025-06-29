/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:49:11 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:49:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	loop_hook(void *param)
{
	t_data	*d;
	double	now;

	d = param;
	now = mlx_get_time();
	if (d->preview_mode && now - d->last_move_time > 0.05)
	{
		d->preview_mode = false;
		d->max_rays = MAX_RAYS;
		d->max_bounces = MAX_BOUNCES;
		reset_pixel_buffer(d);
		render(d, 0, 0);
	}
}
