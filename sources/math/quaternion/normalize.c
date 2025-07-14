/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:29 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:06:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

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
