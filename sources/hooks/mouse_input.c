/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:37 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 17:04:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief True if this mouse event must be ignored; updates last coords.
 * @param d Runtime data.
 * @param mx Mouse X (px).
 * @param my Mouse Y (px).
 * @return true to ignore, false to process.
 */
static bool	mouse_should_ignore(t_data *d, double mx, double my)
{
	double	now;

	if (d->first_mouse)
	{
		d->first_mouse = false;
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return (true);
	}
	now = mlx_get_time();
	if (now < d->mouse_block_until)
	{
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return (true);
	}
	if (d->suppress_next_mouse)
	{
		d->suppress_next_mouse = false;
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return (true);
	}
	return (false);
}

/**
 * @brief Store last mouse coordinates into runtime.
 * @param d Runtime data.
 * @param mx Mouse X (px).
 * @param my Mouse Y (px).
 * @return None.
 */
static void	mouse_update_last(t_data *d, double mx, double my)
{
	d->last_mouse_x = mx;
	d->last_mouse_y = my;
}

/**
 * @brief Accumulate mouse deltas into yaw/pitch with clamping.
 * @param cam Camera (updates yaw/pitch).
 * @param dx Mouse delta X (px).
 * @param dy Mouse delta Y (px).
 * @return None.
 * @note dy is subtracted so moving mouse down looks down (not inverted).
 */
void	mouse_update_angles(t_camera *cam, double dx, double dy)
{
	float	y;
	float	p;

	y = cam->yaw + (float)dx * YAW_SENS;
	p = cam->pitch - (float)dy * PITCH_SENS;
	if (p > PITCH_MAX_RAD)
		p = PITCH_MAX_RAD;
	if (p < -PITCH_MAX_RAD)
		p = -PITCH_MAX_RAD;
	if (y > PI)
		y -= TAU;
	if (y < -PI)
		y += TAU;
	cam->yaw = y;
	cam->pitch = p;
}

/**
 * @brief Mouse move callback: filter, compute deltas, rotate camera.
 * @param mx Mouse X (px).
 * @param my Mouse Y (px).
 * @param param Opaque t_data*.
 * @return None.
 */
void	mouse_move(double mx, double my, void *param)
{
	t_data		*d;
	t_camera	*cam;
	double		dx;
	double		dy;

	d = (t_data *)param;
	cam = d->scene.active_cam;
	if (mouse_should_ignore(d, mx, my))
		return ;
	dx = mx - d->last_mouse_x;
	dy = my - d->last_mouse_y;
	if (mouse_jump_too_large(d, dx, dy))
		return (mouse_update_last(d, mx, my));
	mouse_clamp_deltas(&dx, &dy);
	mouse_update_last(d, mx, my);
	apply_mouse_rotation(d, cam, dx, dy);
}
