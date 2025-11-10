/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:21:38 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

/**
 * @brief Computes the cross product of two vectors (right-hand rule).
 * @param a First vector.
 * @param b Second vector.
 * @return Vector perpendicular to both a and b.
 * @details Math: a×b = (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx).
 */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
