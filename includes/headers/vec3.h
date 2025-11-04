/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:27 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 15:31:07 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# ifndef EPSILON
#  define EPSILON 1e-6f
# endif

# define PI 3.1415927f

# include <math.h>
# include "color.h"
# include <stdint.h>
# include <stdbool.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_pcg
{
	uint64_t	state;
	uint64_t	inc;
}	t_pcg;

t_vec3	vec_normalize(t_vec3 v);
float	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 vec, float scalar);
float	vec_distance(t_vec3 a, t_vec3 b);
float	vec_length(t_vec3 v);
float	degree_to_radian(float degree);
void	pcg_seed(t_pcg *rng, uint64_t initstate, uint64_t initseq);
float	pcg_random_float(t_pcg *rng);
t_color	lerp_colour(t_color c1, t_color c2, float fraction);
t_vec3	lerp_vec(t_vec3 v1, t_vec3 v2, float fraction);
t_vec3	generate_random_ray(t_pcg *rng);

#endif
