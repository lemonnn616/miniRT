/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:26:47 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

/**
 * @brief Scales a vector by a scalar factor.
 * @param vec Input vector.
 * @param scalar Scale factor.
 * @return Scaled vector.
 * @details Math: result = scalar * vec.
 */
t_vec3	vec_scale(t_vec3 vec, float scalar)
{
	t_vec3	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}
