/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:55 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 15:34:35 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/**
 * @brief Computes the Euclidean distance between two points/vectors.
 * @param a First point.
 * @param b Second point.
 * @return Distance between a and b.
 * @details Math: dist(a,b) = ||a - b||.
 */
float	vec_distance(t_vec3 a, t_vec3 b)
{
	t_vec3	diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	return (vec_length(diff));
}
