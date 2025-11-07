/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:12 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 17:01:01 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Reject abnormal jumps (> MOUSE_MAX_PERC of viewport).
 * @param d Runtime data (for width/height).
 * @param dx Delta X (px).
 * @param dy Delta Y (px).
 * @return true to ignore, false to accept.
 */
bool	mouse_jump_too_large(t_data *d, double dx, double dy)
{
	double	max_x;
	double	max_y;

	max_x = (double)d->scene.width * (double)MOUSE_MAX_PERC;
	max_y = (double)d->scene.height * (double)MOUSE_MAX_PERC;
	if (fabs(dx) > max_x || fabs(dy) > max_y)
		return (true);
	return (false);
}

/**
 * @brief Clamp deltas by absolute pixel cap.
 * @param dx In/out delta X.
 * @param dy In/out delta Y.
 * @return None.
 */
void	mouse_clamp_deltas(double *dx, double *dy)
{
	double	cap;

	cap = MOUSE_MAX_PX;
	if (*dx > cap)
		*dx = cap;
	if (*dx < -cap)
		*dx = -cap;
	if (*dy > cap)
		*dy = cap;
	if (*dy < -cap)
		*dy = -cap;
}
