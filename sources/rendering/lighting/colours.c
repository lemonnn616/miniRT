/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:02:45 by natallia          #+#    #+#             */
/*   Updated: 2025/05/18 15:37:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gamma_adjust(t_color *c)
{
	float	gamma;

	gamma = 2.2f;
	c->r = powf(c->r, 1.0f / gamma);
	c->g = powf(c->g, 1.0f / gamma);
	c->b = powf(c->b, 1.0f / gamma);
}

t_color	tint_reflected_light(t_color base_colour, t_color incoming_light)
{
	t_color	result;

	result.r = base_colour.r * incoming_light.r;
	result.g = base_colour.g * incoming_light.g;
	result.b = base_colour.b * incoming_light.b;
	return (result);
}

t_color	blend_ambient_light(t_color base, t_ambient amb, float shininess)
{
	float	amb_total;
	t_color	result;

	if (!amb.is_set)
		return (base);
	amb_total = amb.intensity * (1.0f - shininess);

	// lerp
	// result.r = base.r * (1.0f - amb_total) + amb.color.r * amb_total;
	// result.g = base.g * (1.0f - amb_total) + amb.color.g * amb_total;
	// result.b = base.b * (1.0f - amb_total) + amb.color.b * amb_total;

	result.r = base.r * amb.color.r * amb_total;
	result.g = base.g * amb.color.g * amb_total;
	result.b = base.b * amb.color.b * amb_total;

	// compromise ?
	// result.r = base.r * (amb.color.r * amb_total + (1 - amb_total));
	// result.g = base.g * (amb.color.g * amb_total + (1 - amb_total));
	// result.b = base.b * (amb.color.b * amb_total + (1 - amb_total));
	return (result);
}

t_color	combine_colours(t_color c1, t_color c2)
{
	t_color result;

	result.r = c1.r + (1.0f - c1.r) * c2.r;
	result.g = c1.g + (1.0f - c1.g) * c2.g;
	result.b = c1.b + (1.0f - c1.b) * c2.b;

	return (result);
}
