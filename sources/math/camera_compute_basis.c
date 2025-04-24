/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_compute_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:17:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 17:23:16 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void camera_compute_basis(t_camera *cam)
{
	t_vec3 forward;
	t_vec3 world_up;

	forward  = vec_normalize(cam->dir);
	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	if (fabsf(vec_dot(forward, world_up)) > 0.999f)
		world_up = (t_vec3){1.0f, 0.0f, 0.0f};
	cam->right = vec_normalize(vec_cross(forward, world_up));
	cam->up = vec_cross(cam->right, forward);
}
