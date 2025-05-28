/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:41:56 by natallia          #+#    #+#             */
/*   Updated: 2025/04/29 14:55:43 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialise_mlx_window(t_data *data)
{
	uint32_t	w;
	uint32_t	h;

	w = data->scene.width;
	h = data->scene.height;
	data->mlx = mlx_init(w, h, "miniRT", false);
	if (data->mlx == NULL)
		exit_error(data, "Failed to initialise MLX");
	data->image_buffer = mlx_new_image(data->mlx, w, h);
	if (data->image_buffer == NULL)
		exit_error(data, "Failed to load image buffer");
	if (mlx_image_to_window(data->mlx, data->image_buffer, 0, 0) == -1)
		exit_error(data, "Failed to load window");
}
