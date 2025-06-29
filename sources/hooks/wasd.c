/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:23:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_keys	g_keys = {false, false, false, false};

void	key_cb(mlx_key_data_t key, void *param)
{
	t_data	*d;

	d = param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_W)
			g_keys.w = true;
		if (key.key == MLX_KEY_S)
			g_keys.s = true;
		if (key.key == MLX_KEY_A)
			g_keys.a = true;
		if (key.key == MLX_KEY_D)
			g_keys.d = true;
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(d->mlx);
	}
	else if (key.action == MLX_RELEASE)
	{
		if (key.key == MLX_KEY_W)
			g_keys.w = false;
		if (key.key == MLX_KEY_S)
			g_keys.s = false;
		if (key.key == MLX_KEY_A)
			g_keys.a = false;
		if (key.key == MLX_KEY_D)
			g_keys.d = false;
	}
}

void	update_cb(void *param)
{
	t_data	*d;
	double	now;
	double	delta;
	t_camera	*cam;
	t_vec3	forward;
	t_vec3	right;
	float	speed;
	float	dt;

	d = param;
	now = mlx_get_time();
	delta = now - d->last_move_time;
	if ((g_keys.w || g_keys.a || g_keys.s || g_keys.d) && delta > 0)
	{
		cam = d->scene.active_cam;
		dt = (float)delta;
		camera_compute_basis(cam);
		forward = cam->dir;
		right = cam->right;
		speed = CAMERA_SPEED * dt;
		if (g_keys.w)
			cam->pos = vec_add(cam->pos, vec_scale(forward, speed));
		if (g_keys.s)
			cam->pos = vec_subtract(cam->pos, vec_scale(forward, speed));
		if (g_keys.a)
			cam->pos = vec_subtract(cam->pos, vec_scale(right, speed));
		if (g_keys.d)
			cam->pos = vec_add(cam->pos, vec_scale(right, speed));
		d->last_move_time = now;
		camera_compute_basis(cam);
		reset_pixel_buffer(d);
		recalc_rays_with_orientation(d);
		render(d, 0, 0);
	}
}
