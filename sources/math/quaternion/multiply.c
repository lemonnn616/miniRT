/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:27 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:06:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quat	quat_mul(t_quat a, t_quat b)
{
	t_quat	result;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	result.w = a.w * b.w - vec_dot(a.v, b.v);
	term1 = vec_scale(b.v, a.w);
	term2 = vec_scale(a.v, b.w);
	term3 = vec_cross(a.v, b.v);
	result.v = vec_add(vec_add(term1, term2), term3);
	return (result);
}
