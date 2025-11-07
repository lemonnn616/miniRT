/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:26:31 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:26:57 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Initializes the orientation and orthonormal basis for every camera.
 * @param cam Head of the camera linked list.
 * @return None.
 * @details Computes quaternion mapping (0,0,-1) to cam->dir, then derives
 * (dir, up, right) orthonormal basis via camera_compute_basis().
 */
void	setup_camera_basis(t_camera *cam)
{
	while (cam)
	{
		cam->orient = quat_from_two_vecs((t_vec3){0, 0, -1}, cam->dir);
		camera_compute_basis(cam);
		cam = cam->next;
	}
}
