/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_from_axis_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:22 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:21:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/**
 * @brief Builds a quaternion from an axis–angle representation.
 * @param axis Rotation axis (should be normalized).
 * @param angle Rotation angle in radians.
 * @return Quaternion q = [cos(θ/2), axis * sin(θ/2)].
 * @details If @p axis is not unit-length,
 * rotation magnitude will be scaled by |axis|.
 */
t_quat	quat_from_axis_angle(t_vec3 axis, float angle)
{
	float	half;
	float	s;
	t_quat	q;

	half = angle * 0.5f;
	s = sinf(half);
	q.w = cosf(half);
	q.v = vec_scale(axis, s);
	return (q);
}
