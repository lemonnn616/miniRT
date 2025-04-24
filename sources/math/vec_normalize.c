/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:30:38 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:34:01 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3 vec_normalize(t_vec3 v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < EPSILON)
		return v;
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return v;
}
