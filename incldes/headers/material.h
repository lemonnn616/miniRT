/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:06 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/22 17:20:45 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

typedef struct s_material
{
	t_color	color;
	float	diffuse;
	float	specular;
	float	shininess;
	float	reflectivity;
}	t_material;

#endif
