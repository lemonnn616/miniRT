/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:27 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:45:29 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# ifndef EPSILON
#  define EPSILON 1e-6f
# endif

# define PI 3.1415927f

# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include "color.h"

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

typedef struct s_camera t_camera;

// Vector algebra
t_vec3	vec_normalize(t_vec3 v);
float	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 vec, float scalar);
float	vec_distance(t_vec3 a, t_vec3 b);
float	vec_length(t_vec3 v);

// Angles & random sampling
float	degree_to_radian(float degree);
void	pcg_seed(t_pcg *rng, uint64_t initstate, uint64_t initseq);
float	pcg_random_float(t_pcg *rng);
t_vec3	generate_random_ray(t_pcg *rng);

// Interpolation helpers
t_color	lerp_color(t_color c1, t_color c2, float fraction);
t_vec3	lerp_vec(t_vec3 v1, t_vec3 v2, float fraction);

// Colour utilities
t_color	new_color(float r, float g, float b);
t_color	color_scale(t_color c, float s);
t_color	color_add(t_color a, t_color b);
t_color	combine_colors(t_color c1, t_color c2);
t_color	multiply_colors(t_color a, t_color b);

// Camera helpers
void	camera_compute_basis(t_camera *cam);

#endif
