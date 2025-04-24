/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:18 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 11:57:18 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "light.h"
#include "ambient.h"
#include "object.h"
#include <stdbool.h>

typedef struct s_scene
{
	int	width;
	int	height;
	bool	resolution_set;
	t_camera	*cameras;
	t_camera	*active_cam;
	t_light	*lights;
	t_ambient	ambient;
	t_object	*objects;
}	t_scene;

void	free_scene(t_scene *scene);

#endif
