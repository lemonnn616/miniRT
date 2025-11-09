/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:29 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:15:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/**
 * @brief Normalizes a quaternion if its magnitude is not near zero.
 * @param q Input quaternion.
 * @return Unit quaternion; if magnitude < 1e-6, returns q unchanged.
 * @details Math: |q| = sqrt(w^2 + |v|^2); q_norm = q / |q|.
 */
t_quat	quat_normalize(t_quat q)
{
	float	mag;

	mag = sqrtf(q.w * q.w + vec_dot(q.v, q.v));
	if (mag < 1e-6f)
		return (q);
	q.w /= mag;
	q.v = vec_scale(q.v, 1.0f / mag);
	return (q);
}
