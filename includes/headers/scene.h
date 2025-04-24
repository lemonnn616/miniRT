/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:18 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/22 17:26:50 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "light.h"
#include "ambient.h"
#include "object.h"

typedef struct s_scene
{
	int	width;
	int	height;
	t_camera	*cameras;
	t_camera	*active_cam;
	t_light	*lights;
	t_ambient	ambient;
	t_object	*objects;
}	t_scene;

#endif
