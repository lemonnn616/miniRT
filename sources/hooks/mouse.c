/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/07/17 13:26:17 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_mouse_rotation(t_data *d, t_camera *cam, double dx, double dy)
{
	const double	sens = 0.002;
	t_quat			q_yaw;
	t_quat			q_pitch;
	t_quat			q_rot;

	q_yaw = quat_from_axis_angle(
			(t_vec3){0.0f, 1.0f, 0.0f},
			(float)(dx * sens));
	q_pitch = quat_from_axis_angle(cam->right, (float)(dy * sens));
	q_rot = quat_mul(q_pitch, q_yaw);
	cam->orient = quat_normalize(quat_mul(q_rot, cam->orient));
	camera_compute_basis(cam);
	d->preview_mode = true;
	d->max_rays = 1;
	d->max_bounces = 0;
	d->last_move_time = mlx_get_time();
	rotate_all_objects(d, q_rot);
	recalc_rays_with_orientation(d);
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

void	mouse_move(double mx, double my, void *param)
{
	t_data		*d;
	t_camera	*cam;
	double		dx;
	double		dy;

	d = param;
	cam = d->scene.active_cam;
	dx = mx - d->last_mouse_x;
	dy = my - d->last_mouse_y;
	if (d->first_mouse)
	{
		d->first_mouse = false;
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return ;
	}
	d->last_mouse_x = mx;
	d->last_mouse_y = my;
	apply_mouse_rotation(d, cam, dx, dy);
}
