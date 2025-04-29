#include "debug.h"
#include <stdio.h>

void	debug_print_scene(const t_scene *scene)
{
	int	idx;

	printf("Resolution: %d x %d%s\n",
		scene->width,
		scene->height,
		scene->resolution_set ? "" : " (default)");
	printf("Ambient: intensity=%.2f color=(%u,%u,%u)\n",
		scene->ambient.intensity,
		scene->ambient.color.r,
		scene->ambient.color.g,
		scene->ambient.color.b);
	idx = 0;
	t_camera *cam = scene->cameras;
	while (cam)
	{
		printf("Camera %d: pos=(%.2f,%.2f,%.2f) dir=(%.2f,%.2f,%.2f) "
				"right=(%.2f,%.2f,%.2f) up=(%.2f,%.2f,%.2f) fov=%.2f\n",
				idx++,
				cam->pos.x, cam->pos.y, cam->pos.z,
				cam->dir.x, cam->dir.y, cam->dir.z,
				cam->right.x, cam->right.y, cam->right.z,
				cam->up.x, cam->up.y, cam->up.z,
				cam->fov);
		cam = cam->next;
	}
	idx = 0;
	t_light *l = scene->lights;
	while (l)
	{
		printf("Light %d: pos=(%.2f,%.2f,%.2f) intensity=%.2f color=(%u,%u,%u)\n",
			idx++,
			l->pos.x, l->pos.y, l->pos.z,
			l->intensity,
			l->color.r, l->color.g, l->color.b);
		l = l->next;
	}
	idx = 0;
	t_object *obj = scene->objects;
	while (obj)
	{
		switch (obj->type)
		{
		case OBJ_SPHERE: {
			t_sphere *s = obj->obj;
			printf("Obj %d: Sphere center=(%.2f,%.2f,%.2f) radius=%.2f color=(%u,%u,%u)\n",
				idx++,
				s->center.x, s->center.y, s->center.z,
				s->radius,
				s->mat.color.r, s->mat.color.g, s->mat.color.b);
			break;
		}
		case OBJ_PLANE:
		{
			t_plane *p = obj->obj;
			printf("Obj %d: Plane point=(%.2f,%.2f,%.2f) normal=(%.2f,%.2f,%.2f) color=(%u,%u,%u)\n",
				idx++,
				p->point.x, p->point.y, p->point.z,
				p->normal.x, p->normal.y, p->normal.z,
				p->mat.color.r, p->mat.color.g, p->mat.color.b);
			break;
		}
		case OBJ_CYLINDER:
		{
			t_cylinder *c = obj->obj;
			printf("Obj %d: Cylinder base=(%.2f,%.2f,%.2f) axis=(%.2f,%.2f,%.2f) radius=%.2f height=%.2f color=(%u,%u,%u)\n",
				idx++,
				c->base.x, c->base.y, c->base.z,
				c->axis.x, c->axis.y, c->axis.z,
				c->radius, c->height,
				c->mat.color.r, c->mat.color.g, c->mat.color.b);
			break;
		}
		case OBJ_CONE:
		{
			t_cone *cn = obj->obj;
			printf("Obj %d: Cone apex=(%.2f,%.2f,%.2f) axis=(%.2f,%.2f,%.2f) angle=%.2f height=%.2f color=(%u,%u,%u)\n",
				idx++,
				cn->apex.x, cn->apex.y, cn->apex.z,
				cn->axis.x, cn->axis.y, cn->axis.z,
				cn->angle, cn->height,
				cn->mat.color.r, cn->mat.color.g, cn->mat.color.b);
			break;
		}
		default:
			printf("Obj %d: Unknown type %d\n", idx++, obj->type);
		}
		obj = obj->next;
	}
}
