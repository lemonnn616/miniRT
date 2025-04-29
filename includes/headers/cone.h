/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:35:37 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:36:45 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "vec3.h"
# include "material.h"

typedef struct s_cone
{
	t_vec3		apex;
	t_vec3		axis;
	float		angle;
	float		height;
	t_material	mat;
}	t_cone;

#endif
