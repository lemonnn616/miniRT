/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/22 17:25:04 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	ir;
	float	fov;
	t_vec3	right;
	t_vec3	up;
	struct s_camera *next;
}	t_camera;

#endif
