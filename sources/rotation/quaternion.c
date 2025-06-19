/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:02:53 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/19 19:03:12 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <math.h>

t_quat quat_from_axis_angle(t_vec3 axis, float angle)
{
	float half = angle * 0.5f;
	float s = sinf(half);
	t_quat q;
	q.w = cosf(half);
	q.v = vec_scale(axis, s);
	return	q;
}

t_quat quat_mul(t_quat a, t_quat b)
{
	t_quat result;
	result.w = a.w * b.w - vec_dot(a.v, b.v);
	t_vec3 term1 = vec_scale(b.v, a.w);
	t_vec3 term2 = vec_scale(a.v, b.w);
	t_vec3 term3 = vec_cross(a.v, b.v);
	result.v = vec_add(vec_add(term1, term2), term3);
	return	result;
}

t_quat quat_conj(t_quat q)
{
	t_quat qc;
	qc.w = q.w;
	qc.v = vec_scale(q.v, -1.0f);
	return	qc;
}

t_quat quat_normalize(t_quat q)
{
	float mag = sqrtf(q.w * q.w + vec_dot(q.v, q.v));
	if (mag < 1e-6f) return q;
	q.w /= mag;
	q.v = vec_scale(q.v, 1.0f / mag);
	return	q;
}

t_vec3 quat_rotate_vec(t_vec3 vec, t_quat q)
{
	t_quat p = { .w = 0.0f, .v = vec };
	t_quat qp = quat_mul(q, p);
	t_quat qinv = quat_conj(q);
	t_quat res = quat_mul(qp, qinv);
	return	res.v;
}

/* quaternion_utils.c ------------------------------------------------- */
t_quat quat_from_two_vecs(t_vec3 from, t_vec3 to)
{
	from = vec_normalize(from);
	to   = vec_normalize(to);

	float cosθ = vec_dot(from, to);
	if (cosθ > 0.9999f)
		return (t_quat){ 1, {0,0,0} };
	if (cosθ < -0.9999f)
	{
		t_vec3 axis = fabsf(from.x) < 0.9f ?
						(t_vec3){1,0,0} : (t_vec3){0,1,0};
		axis = vec_normalize(vec_cross(from, axis));
		return quat_from_axis_angle(axis, (float)M_PI);
	}
	t_vec3 axis = vec_cross(from, to);
	float  s	= sqrtf((1 + cosθ)*2);
	float  invs = 1 / s;
	return (t_quat)
	{
		.w = s * 0.5f,
		.v = vec_scale(axis, invs * 0.5f)
	};
}
