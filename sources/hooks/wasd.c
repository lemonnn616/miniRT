/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/07 16:38:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void switch_to_next_camera(t_data *d)
{
	if (!d || !d->scene.cameras || !d->scene.active_cam)
		return ;
	t_camera *next;
	if (d->scene.active_cam->next)
		next = d->scene.active_cam->next;
	else
		next = d->scene.cameras;
	d->scene.active_cam = next;
	camera_compute_basis(next);
	int32_t mx_i = 0, my_i = 0;
	mlx_get_mouse_pos(d->mlx, &mx_i, &my_i);
	d->last_mouse_x = (double)mx_i;
	d->last_mouse_y = (double)my_i;
	d->mouse_block_until = mlx_get_time() + 0.08;
	d->suppress_next_mouse = true;
	d->preview_mode = true;
	d->max_rays = 1;
	d->max_bounces = 0;
	d->last_move_time = mlx_get_time();
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

static void	handle_key_press(t_keys *keys, mlx_key_data_t key, t_data *d)
{
	if (key.key == MLX_KEY_W)
		keys->w = true;
	if (key.key == MLX_KEY_S)
		keys->s = true;
	if (key.key == MLX_KEY_A)
		keys->a = true;
	if (key.key == MLX_KEY_D)
		keys->d = true;
	if (key.key == MLX_KEY_TAB && key.action == MLX_PRESS)
	{
		switch_to_next_camera(d);
		return ;
	}
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		if (!d->exiting)
		{
			d->exiting = true;
			mlx_close_window(d->mlx);
		}
	}
}

static void	handle_key_release(t_keys *keys, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_W)
		keys->w = false;
	if (key.key == MLX_KEY_S)
		keys->s = false;
	if (key.key == MLX_KEY_A)
		keys->a = false;
	if (key.key == MLX_KEY_D)
		keys->d = false;
}

void	key_cb(mlx_key_data_t key, void *param)
{
	t_data	*d;

	d = param;
	if (d->exiting)
		return ;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
		handle_key_press(&d->keys, key, d);
	else if (key.action == MLX_RELEASE)
		handle_key_release(&d->keys, key);
}
