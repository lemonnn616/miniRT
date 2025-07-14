/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:17:43 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
	t_material	mat;
}	t_sphere;

#endif
