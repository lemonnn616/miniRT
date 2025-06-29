/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:17:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/22 20:18:25 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void rotate_plane(t_plane *p, t_quat q_rot)
{
	p->orient = quat_normalize(quat_mul(q_rot, p->orient));
	p->normal = quat_rotate_vec(p->normal0, p->orient);
}

void rotate_cylinder(t_cylinder *c, t_quat q_rot)
{
	c->orient = quat_normalize(quat_mul(q_rot, c->orient));
	c->axis   = quat_rotate_vec(c->axis0, c->orient);
}

void rotate_cone(t_cone *co, t_quat q_rot)
{
	co->orient = quat_normalize(quat_mul(q_rot, co->orient));
	co->axis   = quat_rotate_vec(co->axis0, co->orient);
}

void rotate_square(t_square *sq, t_quat q_rot)
{
	sq->orient = quat_normalize(quat_mul(q_rot, sq->orient));
	sq->normal = quat_rotate_vec(sq->normal0, sq->orient);
}

void rotate_all_objects(t_data *d, t_quat q_rot)
{
	for (t_object *o = d->scene.objects; o; o = o->next)
	{
		if (o->type == OBJ_PLANE)
			rotate_plane   ((t_plane *)	o->obj, q_rot);
		else if (o->type == OBJ_CYLINDER)
			rotate_cylinder((t_cylinder *) o->obj, q_rot);
		else if (o->type == OBJ_CONE)
			rotate_cone	((t_cone *)	 o->obj, q_rot);
		else if (o->type == OBJ_SQUARE)
			rotate_square  ((t_square *)   o->obj, q_rot);
	}
}
