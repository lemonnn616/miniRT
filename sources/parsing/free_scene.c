/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:55:04 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:33:49 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <stdlib.h>

/**
 * @brief Free all cameras in the linked list.
 * @param cam Head of camera list (can be NULL).
 * @return None.
 */
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

/**
 * @brief Free all lights in the linked list.
 * @param light Head of light list (can be NULL).
 * @return None.
 */
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

/**
 * @brief Free all scene objects and
 * the underlying object payloads (except lights twice).
 * @param obj Head of object list.
 * @return None.
 * @details Frees obj->obj for non-light objects
 * (lights are freed via free_lights()).
 */
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

/**
 * @brief Free all dynamic memory associated with a scene (lists only).
 * @param scene Scene pointer (can be NULL).
 * @return None.
 * @details Does not free graphics buffers; use higher-level free_data for that.
 */
void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_cameras(scene->cameras);
	free_lights(scene->lights);
	free_objects(scene->objects);
}
