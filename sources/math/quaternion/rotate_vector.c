/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 15:53:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/**
 * @brief Rotates a 3D vector by a quaternion.
 * @param vec Input vector to rotate.
 * @param q Rotation quaternion (ideally normalized).
 * @return Rotated vector q * (0,vec) * conj(q).
 * @details Math: v' = q v q^{-1}, where v is pure quaternion (0,vec).
 */
t_vec3	quat_rotate_vec(t_vec3 vec, t_quat q)
{
	t_quat	p;
	t_quat	qp;
	t_quat	qinv;
	t_quat	res;

	p = (t_quat){.w = 0.0f, .v = vec};
	qp = quat_mul(q, p);
	qinv = quat_conj(q);
	res = quat_mul(qp, qinv);
	return (res.v);
}
