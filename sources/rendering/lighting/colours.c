/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:02:45 by natallia          #+#    #+#             */
/*   Updated: 2025/05/19 12:23:59 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	gamma_adjust(t_color *c)
// {
// 	float	gamma;

// 	gamma = 2.2f;
// 	c->r = powf(c->r, 1.0f / gamma);
// 	c->g = powf(c->g, 1.0f / gamma);
// 	c->b = powf(c->b, 1.0f / gamma);
// }

// t_color	tint_reflected_light(t_color base_colour, t_color incoming_light)
// {
// 	t_color	result;

// 	result.r = base_colour.r * incoming_light.r;
// 	result.g = base_colour.g * incoming_light.g;
// 	result.b = base_colour.b * incoming_light.b;
// 	return (result);
// }

// t_color	blend_ambient_light(t_color base, t_ambient amb, float shininess)
// {
// 	float	amb_total;
// 	t_color	result;

// 	if (!amb.is_set)
// 		return (base);
// 	amb_total = amb.intensity * (1.0f - shininess);
// 	result.r = base.r * amb.color.r * amb_total;
// 	result.g = base.g * amb.color.g * amb_total;
// 	result.b = base.b * amb.color.b * amb_total;
// 	return (result);
// }

// t_color	combine_colours(t_color c1, t_color c2)
// {
// 	t_color result;

// 	result.r = c1.r + (1.0f - c1.r) * c2.r;
// 	result.g = c1.g + (1.0f - c1.g) * c2.g;
// 	result.b = c1.b + (1.0f - c1.b) * c2.b;

// 	return (result);
// }

void	gamma_adjust(t_color *c)
{
	float	r, g, b;
	float	gamma = 2.2f;

	color_to_float(*c, &r, &g, &b);
	r = powf(r, 1.0f / gamma);
	g = powf(g, 1.0f / gamma);
	b = powf(b, 1.0f / gamma);
	*c = float_to_color(r, g, b);
}

t_color	tint_reflected_light(t_color base_colour, t_color incoming_light)
{
	float	br, bg, bb, ir, ig, ib;

	color_to_float(base_colour, &br, &bg, &bb);
	color_to_float(incoming_light, &ir, &ig, &ib);
	return (float_to_color(br * ir, bg * ig, bb * ib));
}

t_color	blend_ambient_light(t_color base, t_ambient amb, float shininess)
{
	float	br, bg, bb, ar, ag, ab, amb_total;

	if (!amb.is_set)
		return base;
	color_to_float(base, &br, &bg, &bb);
	color_to_float(amb.color, &ar, &ag, &ab);
	amb_total = amb.intensity * (1.0f - shininess);
	return (float_to_color(
		br * ar * amb_total,
		bg * ag * amb_total,
		bb * ab * amb_total
	));
}

t_color	combine_colours(t_color c1, t_color c2)
{
	float	r1, g1, b1, r2, g2, b2;

	color_to_float(c1, &r1, &g1, &b1);
	color_to_float(c2, &r2, &g2, &b2);
	return (float_to_color(
		r1 + (1.0f - r1) * r2,
		g1 + (1.0f - g1) * g2,
		b1 + (1.0f - b1) * b2
	));
}
