/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/09/26 18:25:58 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
