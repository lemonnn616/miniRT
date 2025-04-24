/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 17:19:02 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	float	fov;
	t_vec3	right;
	t_vec3	up;
	struct s_camera *next;
}	t_camera;

void	camera_compute_basis(t_camera *cam);

#endif
