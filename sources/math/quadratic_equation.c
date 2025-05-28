/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:16 by natallia          #+#    #+#             */
/*   Updated: 2025/05/01 10:17:28 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

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
