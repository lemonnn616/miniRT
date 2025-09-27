/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:55:04 by iriadyns          #+#    #+#             */
/*   Updated: 2025/09/26 19:27:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <stdlib.h>

static void	free_cameras(t_camera *cam)
{
	t_camera	*next;

	while (cam)
	{
		next = cam->next;
		free(cam);
		cam = next;
	}
}

static void	free_lights(t_light *light)
{
	t_light	*next;

	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}

static void	free_objects(t_object *obj)
{
	t_object	*next;

	while (obj)
	{
		next = obj->next;
		if (obj->obj && obj->type != OBJ_LIGHT)
			free(obj->obj);
		free(obj);
		obj = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_cameras(scene->cameras);
	free_lights(scene->lights);
	free_objects(scene->objects);
}
