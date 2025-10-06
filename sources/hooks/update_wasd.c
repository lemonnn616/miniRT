/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_wasd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:40:59 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/06 16:32:16 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_camera_position(t_data *d, t_camera *cam, float speed)
{
	if (d->keys.w)
		cam->pos = vec_add(cam->pos, vec_scale(cam->dir, speed));
	if (d->keys.s)
		cam->pos = vec_subtract(cam->pos, vec_scale(cam->dir, speed));
	if (d->keys.a)
		cam->pos = vec_subtract(cam->pos, vec_scale(cam->right, speed));
	if (d->keys.d)
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, speed));
}

static void	process_movement(t_data *d, t_camera *cam, float speed)
{
	update_camera_position(d, cam, speed);
	d->last_move_time = mlx_get_time();
	camera_compute_basis(cam);
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

static void	prepare_movement(t_data *d, double delta)
{
	t_camera	*cam;
	// t_vec3		forward;
	// t_vec3		right;
	float		speed;
	float		dt;

	cam = d->scene.active_cam;
	dt = (float)delta;
	camera_compute_basis(cam);
	// forward = cam->dir;
	// right = cam->right;
	speed = CAMERA_SPEED * dt;
	process_movement(d, cam, speed);
}

void	update_cb(void *param)
{
	t_data	*d;
	double	now;
	double	delta;

	d = param;
	now = mlx_get_time();
	delta = now - d->last_frame_time;
	if (delta < 0.0)
		delta = 0.0;
	if (delta > 0.05)
		delta = 0.05;
	d->last_frame_time = now;
	if ((d->keys.w || d->keys.a || d->keys.s || d->keys.d) && delta > 0.0)
		prepare_movement(d, (float)delta);
}
