/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:27 by iriadyns          #+#    #+#             */
/*   Updated: 2025/05/07 11:59:43 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# ifndef EPSILON
#  define EPSILON 1e-6f
# endif

# define PI 3.1415927f

# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	vec_normalize(t_vec3 v);
float	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 vec, float scalar);
float	vec_distance(t_vec3 a, t_vec3 b);
float	vec_length(t_vec3 v);
float	degree_to_radian(float degree);
bool	quadratic_equation(t_vec3 quad_coeff, float *roots);

#endif
