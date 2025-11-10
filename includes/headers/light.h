/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:25:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:55:06 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <stdbool.h>
# include <stdint.h>
# include <math.h>
# include "rt_math.h"
# include "color.h"
# include "ambient.h"

typedef struct s_data	t_data;
typedef struct s_hit	t_hit;
typedef struct s_ray	t_ray;
typedef struct s_pixel	t_pixel;
typedef struct s_dlctx	t_dlctx;

# ifndef GLOBE_RADIUS
#  define GLOBE_RADIUS 0.5f
# endif

typedef struct s_light
{
	t_vec3			pos;
	float			intensity;
	t_color			color;
	struct s_light	*next;
}	t_light;

// Light sampling & direct lighting entry points
t_color		sample_direct_lights(t_data *data, t_hit *hit,
				t_vec3 view_dir, t_pcg *rng);
void		integrate_direct_lighting(t_data *d, t_ray *r,
				t_pixel *pxl, t_color *throughput);

// Reflection sampling and micro-utility functions
bool		random_is_specular(t_pcg *rng, float reflectivity);
void		gamma_adjust(t_color *c);
uint32_t	percentage_to_rgba(const t_color f);
t_vec3		cosine_weighted_hemisphere(t_pcg *rng, const t_vec3 normal);

// Per-light contribution (area/point)
t_color		eval_area_light(t_dlctx *c, t_light *l, int m);
t_color		eval_point_light(t_data *d, t_hit *h, t_light *l, t_vec3 view_dir);

// Local shading components
t_color		compute_diffuse(t_light *l, t_hit *h, float n_dot_l);
t_color		compute_specular(t_light *l, t_hit *h,
				t_vec3 view_dir, t_vec3 l_dir);

// Visibility, shadows & ambient blend
bool		is_in_shadow(t_data *d, t_hit *hit, t_vec3 light_dir, float dist);
t_color		blend_ambient_light(t_color base, t_ambient amb, float shininess);

#endif
