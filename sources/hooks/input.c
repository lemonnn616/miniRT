/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:42:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 13:42:54 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool   first_mouse = true;
static double last_x, last_y;
static t_keys keys = { false, false, false, false };

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

void key_cb(mlx_key_data_t key, void *param)
{
	t_data *d = param;

	if (key.action == MLX_PRESS || key.action == MLX_REPEAT) {
		if (key.key == MLX_KEY_W) keys.w = true;
		if (key.key == MLX_KEY_S) keys.s = true;
		if (key.key == MLX_KEY_A) keys.a = true;
		if (key.key == MLX_KEY_D) keys.d = true;
		if (key.key == MLX_KEY_ESCAPE) mlx_close_window(d->mlx);
	} else if (key.action == MLX_RELEASE) {
		if (key.key == MLX_KEY_W) keys.w = false;
		if (key.key == MLX_KEY_S) keys.s = false;
		if (key.key == MLX_KEY_A) keys.a = false;
		if (key.key == MLX_KEY_D) keys.d = false;
	}
}

void update_cb(void *param)
{
	t_data *d   = param;
	double now  = mlx_get_time();
	double delta = now - d->last_move_time;

	if ((keys.w || keys.a || keys.s || keys.d) && delta > 0) {
		t_camera *cam = d->scene.active_cam;
		float dt = (float)delta;
		camera_compute_basis(cam);
		t_vec3 forward = cam->dir;
		t_vec3 right   = cam->right;
		float  speed   = CAMERA_SPEED * dt;

		if (keys.w)
			cam->pos = vec_add(cam->pos, vec_scale(forward, speed));
		if (keys.s)
			cam->pos = vec_subtract(cam->pos, vec_scale(forward, speed));
		if (keys.a)
			cam->pos = vec_subtract(cam->pos, vec_scale(right, speed));
		if (keys.d)
			cam->pos = vec_add(cam->pos, vec_scale(right, speed));
		d->last_move_time = now;
		camera_compute_basis(cam);
		reset_pixel_buffer(d);
		recalc_rays_with_orientation(d);
		render(d, 0, 0);
	}
}

void reset_pixel_buffer(t_data *d)
{
	for (int y = 0; y < d->scene.height; ++y)
		for (int x = 0; x < d->scene.width; ++x)
		{
			t_pixel *p = &d->pixels[y][x];
			p->colour_sum = new_colour(0,0,0);
			p->final_colour = new_colour(0,0,0);
			p->ambient = new_colour(0,0,0);
		}
}

void recalc_rays_with_orientation(t_data *data)
{
	cast_rays(data);
	t_camera *cam = data->scene.active_cam;
	for (int y = 0; y < data->scene.height; ++y)
	{
		for (int x = 0; x < data->scene.width; ++x)
		{
			t_vec3 v = data->pixels[y][x].ray_direction;
			t_vec3 world =
				vec_add(
					vec_add(
						vec_scale(cam->right, v.x),
						vec_scale(cam->up,	v.y)),
					vec_scale(cam->dir,	 v.z));
			data->pixels[y][x].ray_direction = vec_normalize(world);
		}
	}
}