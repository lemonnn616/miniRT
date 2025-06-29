/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:06:43 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

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
