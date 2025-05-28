/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:37:10 by natallia          #+#    #+#             */
/*   Updated: 2025/05/19 12:20:10 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_color	colour_scale(t_color c, float s)
// {
// 	c.r *= s;
// 	c.g *= s;
// 	c.b *= s;
// 	return (c);
// }

// t_color	colour_add(t_color a, t_color b)
// {
// 	t_color	result;

// 	result.r = a.r + b.r;
// 	result.g = a.g + b.g;
// 	result.b = a.b + b.b;
// 	return (result);
// }

// t_color	new_colour(float r, float g, float b)
// {
// 	t_color	c;

// 	c.r = r;
// 	c.g = g;
// 	c.b = b;
// 	return (c);
// }

void	color_to_float(t_color c, float *r, float *g, float *b)
{
	*r = c.r / 255.0f;
	*g = c.g / 255.0f;
	*b = c.b / 255.0f;
}

t_color	float_to_color(float r, float g, float b)
{
	t_color	c;

	if (r < 0) r = 0; else if (r > 1) r = 1;
	if (g < 0) g = 0; else if (g > 1) g = 1;
	if (b < 0) b = 0; else if (b > 1) b = 1;

	c.r = (uint8_t)(r * 255.0f);
	c.g = (uint8_t)(g * 255.0f);
	c.b = (uint8_t)(b * 255.0f);
	return (c);
}

t_color	colour_scale(t_color c, float s)
{
	float	r, g, b;

	color_to_float(c, &r, &g, &b);
	r *= s;
	g *= s;
	b *= s;
	return (float_to_color(r, g, b));
}

t_color	colour_add(t_color a, t_color b)
{
	float	r1, g1, b1, r2, g2, b2;

	color_to_float(a, &r1, &g1, &b1);
	color_to_float(b, &r2, &g2, &b2);
	return (float_to_color(r1 + r2, g1 + g2, b1 + b2));
}

t_color	new_colour(float r, float g, float b)
{
	return (float_to_color(r, g, b));
}
