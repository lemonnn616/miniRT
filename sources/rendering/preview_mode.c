/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:19:28 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 20:20:33 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prepare_preview(t_data *data, t_ray *ray, uint32_t y_start, uint32_t x)
{
	t_color	direct;
	t_color	preview;

	direct = sample_direct_lights(data, ray->hit_data,
			vec_scale(ray->direction, -1.0f));
	preview = colour_add(direct, data->pixels[y_start][x].ambient);
	gamma_adjust(&preview);
	data->pixels[y_start][x].final_colour = preview;
}
