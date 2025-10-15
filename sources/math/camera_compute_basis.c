/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_compute_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:02:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/06 16:07:50 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_compute_basis(t_camera *cam)
{
	const t_vec3	f0 = {0.0f, 0.0f, -1.0f};
	const t_vec3	u0 = {0.0f, 1.0f, 0.0f};

	cam->dir   = vec_normalize(quat_rotate_vec(f0, cam->orient));
	cam->up    = vec_normalize(quat_rotate_vec(u0, cam->orient));
	cam->right = vec_normalize(vec_cross(cam->up, cam->dir));
	cam->up    = vec_normalize(vec_cross(cam->dir, cam->right));
}
