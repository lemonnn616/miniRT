/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_compute_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:02:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 15:38:04 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

/**
 * @brief Recomputes the camera’s orthonormal basis (dir, up, right)
 * from its quaternion orientation.
 * @param cam Camera object; reads cam->orient
 * and writes cam->dir, cam->up, cam->right.
 * @return None.
 * @details
 *  Math:
 *   dir   = normalize( rotate_q( (0,0,-1), orient ) )
 *   up    = normalize( rotate_q( (0,1, 0), orient ) )
 *   right = normalize( up × dir )
 *   up    = normalize( dir × right )  // re-orthogonalize
 */
void	camera_compute_basis(t_camera *cam)
{
	const t_vec3	f0 = {0.0f, 0.0f, -1.0f};
	const t_vec3	u0 = {0.0f, 1.0f, 0.0f};

	cam->dir = vec_normalize(quat_rotate_vec(f0, cam->orient));
	cam->up = vec_normalize(quat_rotate_vec(u0, cam->orient));
	cam->right = vec_normalize(vec_cross(cam->up, cam->dir));
	cam->up = vec_normalize(vec_cross(cam->dir, cam->right));
}
