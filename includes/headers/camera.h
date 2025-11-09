/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:18:56 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec3.h"
# include "quaternion.h"

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir;
	t_quat			orient;
	float			fov;
	t_vec3			right;
	t_vec3			up;
	struct s_camera	*next;
	float			yaw;
	float			pitch;
	bool			angles_set;
}	t_camera;

void	camera_compute_basis(t_camera *cam);

#endif
