/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:35:37 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:17:25 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "vec3.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_cone
{
	t_vec3		apex;
	t_vec3		axis;
	float		angle;
	float		height;
	t_quat		orient;
	t_vec3		axis0;
	t_material	mat;
}	t_cone;

#endif
