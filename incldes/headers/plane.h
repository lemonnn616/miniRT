/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/22 17:21:53 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "material.h"

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_material	mat;
}	t_plane;

#endif
