/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:23:46 by iriadyns          #+#    #+#             */
/*   Updated: 2025/05/08 14:46:42 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "triangle.h"
# include "square.h"
# include "cone.h"

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_TRIANGLE,
	OBJ_SQUARE,
	OBJ_CONE,
	OBJ_LIGHT,
	OBJ_NONE
}	t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	void			*obj;
	struct s_object	*next;
}	t_object;

#endif
