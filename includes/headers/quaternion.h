/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:10:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:13:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "vec3.h"

typedef struct s_quat
{
	float	w;
	t_vec3	v;
}	t_quat;

t_quat	quat_from_axis_angle(t_vec3 axis, float angle);
t_quat	quat_mul(t_quat a, t_quat b);
t_quat	quat_conj(t_quat q);
t_quat	quat_normalize(t_quat q);
t_vec3	quat_rotate_vec(t_vec3 vec, t_quat q);
t_quat	quat_from_two_vecs(t_vec3 from, t_vec3 to);
bool	quadratic_equation(t_vec3 quad_coeff, float *roots);

#endif