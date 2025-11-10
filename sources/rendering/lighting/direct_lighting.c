/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:09:29 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 10:21:36 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	light_spp_for_hit(const t_hit *h, const t_light *l, int base)
{
	float	dist;
	float	r_over_d;

	if (GLOBE_RADIUS <= 0.0f)
		return (1);
	dist = vec_length(vec_subtract(l->pos, h->location));
	if (dist <= 0.0f)
		return (1);
	r_over_d = GLOBE_RADIUS / dist;
	if (r_over_d < 0.02f)
		return (1);
	if (r_over_d < 0.05f)
	{
		if (base < 2)
			return (base);
		return (2);
	}
	if (r_over_d < 0.10f)
	{
		if (base < 3)
			return (base);
		return (3);
	}
	return (base);
}

t_color	sample_direct_lights(t_data *d, t_hit *h, t_vec3 view_dir, t_pcg *rng)
{
	t_light	*light;
	t_color	total;
	t_dlctx	c;
	int		base;

	light = d->scene.lights;
	total = new_colour(0, 0, 0);
	c.data = d;
	c.hit = h;
	c.view_dir = view_dir;
	c.rng = rng;
	base = 4;
	if (d->preview_mode == true)
		base = 1;
	while (light)
	{
		if (GLOBE_RADIUS > 0.0f)
			total = colour_add(total, eval_area_light(&c, light,
						light_spp_for_hit(h, light, base)));
		else
			total = colour_add(total,
					eval_point_light(d, h, light, view_dir));
		light = light->next;
	}
	return (total);
}

void	integrate_direct_lighting(t_data *d, t_ray *r,
	t_pixel *pxl, t_color *throughput)
{
	t_color	direct;
	t_color	contrib;
	t_vec3	view_dir;

	view_dir = vec_scale(r->direction, -1.0f);
	direct = sample_direct_lights(d, r->hit_data, view_dir, r->rng);
	contrib = multiply_colours(*throughput, direct);
	pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
}
