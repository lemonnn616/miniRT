/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:49:11 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:58:44 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Frame loop hook: exits preview mode after a short idle period.
 * @param param Opaque pointer to t_data.
 * @details If preview mode is active and there was no movement for > 50 ms,
 * restores MAX_RAYS and MAX_BOUNCES, clears the pixel buffer and restarts
 * progressive rendering.
 */
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
		start_progressive_render(d);
	}
}
