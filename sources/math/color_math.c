/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:37:10 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 17:21:13 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_scale(t_color c, float s)
{
	c.r *= s;
	c.g *= s;
	c.b *= s;
	return (c);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

t_color	new_color(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	combine_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + (1.0f - c1.r) * c2.r;
	result.g = c1.g + (1.0f - c1.g) * c2.g;
	result.b = c1.b + (1.0f - c1.b) * c2.b;
	return (result);
}

t_color	multiply_colors(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}
