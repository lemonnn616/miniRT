/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:37:10 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 15:37:21 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Scales a color by a scalar (per component).
 * @param c Input color (linear space, 0..1).
 * @param s Scale factor.
 * @return Scaled color (no clamping).
 * @details Math: c' = s * c.
 */
t_color	colour_scale(t_color c, float s)
{
	c.r *= s;
	c.g *= s;
	c.b *= s;
	return (c);
}

/**
 * @brief Component-wise addition of two colors.
 * @param a First color.
 * @param b Second color.
 * @return Sum color (no clamping).
 * @details Math: c = a + b.
 */
t_color	colour_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

/**
 * @brief Constructs a color from r,g,b components.
 * @param r Red component (0..1).
 * @param g Green component (0..1).
 * @param b Blue component (0..1).
 * @return New color {r,g,b}.
 */
t_color	new_colour(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/**
 * @brief Combines two colors with a simple over-like heuristic (no alpha).
 * @param c1 Base color.
 * @param c2 Overlay color.
 * @return Combined color.
 * @details Math: out = c1 + (1 - c1) * c2 (applied per component).
 */
t_color	combine_colours(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + (1.0f - c1.r) * c2.r;
	result.g = c1.g + (1.0f - c1.g) * c2.g;
	result.b = c1.b + (1.0f - c1.b) * c2.b;
	return (result);
}

/**
 * @brief Component-wise (Hadamard) product of two colors.
 * @param a First color.
 * @param b Second color.
 * @return Product color.
 * @details Math: c = a ⊙ b = (ar*br, ag*bg, ab*bb).
 */
t_color	multiply_colours(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}
