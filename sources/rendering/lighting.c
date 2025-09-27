/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:02:45 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 14:23:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	blend_ambient_light(t_color base, t_ambient amb, float shininess)
{
	float	amb_total;
	t_color	result;

	if (!amb.is_set)
		return (base);
	amb_total = amb.intensity * (1.0f - shininess);
	result.r = base.r * amb.color.r * amb_total;
	result.g = base.g * amb.color.g * amb_total;
	result.b = base.b * amb.color.b * amb_total;
	return (result);
}

uint32_t	percentage_to_rgba(const t_color f)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)(f.r * 255.0f);
	g = (uint8_t)(f.g * 255.0f);
	b = (uint8_t)(f.b * 255.0f);
	a = 0xFF;
	return (r << 24 | g << 16 | b <<  8 | a);
}

void	gamma_adjust(t_color *c)
{
	float	gamma;

	gamma = 2.2f;
	c->r = powf(c->r, 1.0f / gamma);
	c->g = powf(c->g, 1.0f / gamma);
	c->b = powf(c->b, 1.0f / gamma);
}
