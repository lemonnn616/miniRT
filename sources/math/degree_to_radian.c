/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree_to_radian.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:12:08 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 15:35:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/**
 * @brief Converts degrees to radians.
 * @param degree Angle in degrees.
 * @return Angle in radians.
 * @details Math: rad = deg * π / 180.
 */
float	degree_to_radian(float degree)
{
	return (degree * PI / 180.0f);
}
