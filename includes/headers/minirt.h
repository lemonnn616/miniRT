/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:27:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/22 17:27:41 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "vec3.h"
#include "color.h"
#include "material.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "triangle.h"
#include "square.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "ambient.h"
#include "scene.h"
#include "parser.h"

bool	render_scene(t_scene *scene);
void	camera_compute_basis(t_camera *cam);
void	free_scene(t_scene *scene);

#endif
