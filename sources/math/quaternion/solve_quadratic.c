/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 14:05:57 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

bool	quadratic_equation(t_vec3 quad_coeff, float *roots)
{
	float	discriminant;
	float	temp;

	if (fabs(quad_coeff.x) < EPSILON)
		return (false);
	discriminant = quad_coeff.y * quad_coeff.y
		- 4.0f * quad_coeff.x * quad_coeff.z;
	if (discriminant < 0)
		return (false);
	roots[0] = (-quad_coeff.y - sqrtf(discriminant)) / (2 * quad_coeff.x);
	roots[1] = (-quad_coeff.y + sqrtf(discriminant)) / (2 * quad_coeff.x);
	if (roots[0] > roots[1])
	{
		temp = roots[0];
		roots[0] = roots[1];
		roots[1] = temp;
	}
	return (true);
}
