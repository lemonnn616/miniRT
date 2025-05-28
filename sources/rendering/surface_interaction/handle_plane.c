/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:51 by natallia          #+#    #+#             */
/*   Updated: 2025/05/15 18:26:06 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_plane_surface_interaction(t_hit *hit)
{
	if (hit->reflection_ray == false)
		hit->colour = tint_reflected_light(hit->obj_colour, hit->colour);
}
