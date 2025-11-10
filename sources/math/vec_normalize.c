/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:30:38 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

/**
 * @brief Normalizes a vector to unit length if its magnitude is not near zero.
 * @param v Input vector.
 * @return Normalized vector; if ||v|| < EPSILON, returns v unchanged.
 * @details Math: ||v|| = sqrt(x^2 + y^2 + z^2), v_norm = v / ||v||.
 */
t_vec3	vec_normalize(t_vec3 v)
{
	float	len;

	len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < EPSILON)
		return (v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}
