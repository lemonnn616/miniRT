/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:22:08 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/22 20:16:19 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool   first_mouse = true;
static double last_x, last_y;

void mouse_move(double mx, double my, void *param)
{
	t_data   *data = param;
	t_camera *cam  = data->scene.active_cam;

	const double sens = 0.002;
	double dx = mx - last_x;
	double dy = my - last_y;

	if (first_mouse)
	{
		first_mouse = false;
		last_x = mx;
		last_y = my;
		return;
	}
	last_x = mx;
	last_y = my;
	t_quat q_yaw = quat_from_axis_angle((t_vec3){0,1,0}, (float)(dx * sens));
	t_quat q_pitch = quat_from_axis_angle(cam->right, (float)(dy * sens));
	t_quat q_rot = quat_mul(q_pitch, q_yaw);
	cam->orient = quat_normalize(quat_mul(q_rot, cam->orient));
	camera_compute_basis(cam);
	data->preview_mode = true;
	data->max_rays = 1;
	data->max_bounces = 0;
	data->last_move_time = mlx_get_time();
	rotate_all_objects(data, q_rot);
	recalc_rays_with_orientation(data);
	reset_pixel_buffer(data);
	render(data, 0, 0);
}