/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:53 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 15:34:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/**
 * @brief Computes the Euclidean length (magnitude) of a vector.
 * @param v Input vector.
 * @return Non-negative length of v.
 * @details Math: ||v|| = sqrt(x^2 + y^2 + z^2).
 */
float	vec_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
