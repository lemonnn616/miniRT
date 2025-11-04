/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:22:55 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/**
 * @brief Solves a quadratic equation a*t^2 + b*t + c = 0
 * using coefficients in a vector.
 * @param quad_coeff Coefficients packed as {a, b, c}.
 * @param roots Output array of size 2;
 * on success returns real roots sorted ascending.
 * @return true if real roots exist and a is not ~0; false otherwise.
 * @details Math: D = b^2 - 4ac; t0,1 = (-b ± sqrt(D)) / (2a).
 * Rejects when |a|<EPSILON or D<0.
 */
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
