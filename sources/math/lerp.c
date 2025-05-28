/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:30:44 by natallia          #+#    #+#             */
/*   Updated: 2025/05/18 13:31:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_color	lerp_colour(t_color c1, t_color c2, float fraction)
{
	t_color	res;

	res.r = c1.r * (1 - fraction) + c2.r * fraction;
	res.g = c1.g * (1 - fraction) + c2.g * fraction;
	res.b = c1.b * (1 - fraction) + c2.b * fraction;
	return (res);
}

t_vec3	lerp_vec(t_vec3 v1, t_vec3 v2, float fraction)
{
	t_vec3	res;

	res.x = v1.x * (1.0f - fraction) + v2.x * fraction;
	res.y = v1.y * (1.0f - fraction) + v2.y * fraction;
	res.z = v1.z * (1.0f - fraction) + v2.z * fraction;
	return (res);
}
