/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 19:00:35 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Cycle to the next camera and restart preview rendering.
 * @param d Global runtime data.
 * @return None.
 * @details Advances active_cam to its next node (or wraps to head), recomputes
 * basis, synchronizes last mouse position with current cursor, temporarily
 * suppresses the next mouse event, and switches to preview render (1 spp, 0 bounces).
 */
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

/**
 * @brief Handle key press/repeat events (WASD, TAB, ESC).
 * @param keys Key state structure to mutate.
 * @param key MLX key event.
 * @param d Global runtime data (for camera switch and exit).
 * @return None.
 * @details Sets movement booleans, switches camera on TAB, closes window on ESC.
 */
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

/**
 * @brief Handle key release events (WASD).
 * @param keys Key state structure to mutate.
 * @param key MLX key event.
 * @return None.
 */
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

/**
 * @brief MLX keyboard callback: dispatch press/repeat/release.
 * @param key MLX key event.
 * @param param Opaque pointer to t_data.
 * @return None.
 * @details Ignores events if an exit is already in progress.
 */
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
