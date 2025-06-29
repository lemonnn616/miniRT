/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_from_two_vectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:25 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:12:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

static t_quat	handle_opposite_vectors(t_vec3 from)
{
	t_vec3	axis;

	if (fabsf(from.x) < 0.9f)
		axis = (t_vec3){1.0f, 0.0f, 0.0f};
	else
		axis = (t_vec3){0.0f, 1.0f, 0.0f};
	axis = vec_normalize(vec_cross(from, axis));
	return (quat_from_axis_angle(axis, (float)M_PI));
}

t_quat	quat_from_two_vecs(t_vec3 from, t_vec3 to)
{
	t_vec3	axis;
	float	cos_theta;
	float	s;
	float	invs;

	from = vec_normalize(from);
	to = vec_normalize(to);
	cos_theta = vec_dot(from, to);
	if (cos_theta > 0.9999f)
		return ((t_quat){1.0f, {0.0f, 0.0f, 0.0f}});
	if (cos_theta < -0.9999f)
		return (handle_opposite_vectors(from));
	axis = vec_cross(from, to);
	s = sqrtf((1.0f + cos_theta) * 2.0f);
	invs = 1.0f / s;
	return ((t_quat){
		.w = s * 0.5f,
		.v = vec_scale(axis, invs * 0.5f)
	});
}
