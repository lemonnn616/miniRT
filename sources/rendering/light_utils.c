/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:02:45 by natallia          #+#    #+#             */
/*   Updated: 2025/11/03 15:30:44 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	integrate_direct_lighting(t_data *d, t_ray *r,
	t_pixel *pxl, t_color *throughput)
{
	t_color	direct;
	t_color	contrib;
	t_vec3	view_dir;

	view_dir = vec_scale(r->direction, -1.0f);
	direct = sample_direct_lights(d, r->hit_data, view_dir);
	contrib = multiply_colours(*throughput, direct);
	pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
}

bool	random_is_specular(t_pcg *rng, float shininess)
{
	float	random;

	random = pcg_random_float(rng);
	if (random <= shininess)
		return (true);
	return (false);
}

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

static float	clamp01(float v)
{
	if (v < 0.0f)
		return (0.0f);
	if (v > 1.0f)
		return (1.0f);
	return (v);
}

uint32_t	percentage_to_rgba(const t_color f)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	float	rr;
	float	gg;
	float	bb;

	rr = clamp01(f.r);
	gg = clamp01(f.g);
	bb = clamp01(f.b);
	r = (uint8_t)(rr * 255.0f);
	g = (uint8_t)(gg * 255.0f);
	b = (uint8_t)(bb * 255.0f);
	a = 0xFF;
	return (r << 24 | g << 16 | b << 8 | a);
}

void	gamma_adjust(t_color *c)
{
	float	gamma;

	gamma = 2.2f;
	c->r = powf(c->r, 1.0f / gamma);
	c->g = powf(c->g, 1.0f / gamma);
	c->b = powf(c->b, 1.0f / gamma);
}
