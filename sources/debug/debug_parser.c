#include "debug.h"
#include <stdio.h>

static const char	*obj_type_str(t_obj_type t)
{
	if (t == OBJ_SPHERE) return "Sphere";
	else if (t == OBJ_PLANE) return "Plane";
	else if (t == OBJ_CYLINDER) return "Cylinder";
	else if (t == OBJ_TRIANGLE) return "Triangle";
	else if (t == OBJ_SQUARE) return "Square";
	else if (t == OBJ_CONE) return "Cone";
	else if (t == OBJ_LIGHT) return "Light";
	else return "Unknown";
}

static void	print_vec(const char *label, t_vec3 v)
{
	printf("%s=(%.2f,%.2f,%.2f)", label, v.x, v.y, v.z);
}

static void	print_col(const char *label, t_color c)
{
	printf("%s=(%.2f,%.2f,%.2f)", label, c.r, c.g, c.b);
}

void	debug_print_scene(const t_scene *scene)
{
	int			idx;
	t_camera	*cam;
	t_light		*l;
	t_object	*obj;

	printf("Resolution: %d x %d%s\n",
		scene->width, scene->height,
		scene->resolution_set ? "" : " (default)");
	printf("Ambient: intensity=%.2f ", scene->ambient.intensity);
	print_col("color", scene->ambient.color);
	printf("\n");

	idx = 0;
	cam = scene->cameras;
	while (cam)
	{
		printf("Camera %d: ", idx);
		print_vec("pos", cam->pos);
		printf(" ");
		print_vec("dir", cam->dir);
		printf(" ");
		print_vec("right", cam->right);
		printf(" ");
		print_vec("up", cam->up);
		printf(" fov=%.2f\n", cam->fov);
		idx++;
		cam = cam->next;
	}

	idx = 0;
	l = scene->lights;
	while (l)
	{
		printf("Light %d: ", idx);
		print_vec("pos", l->pos);
		printf(" intensity=%.2f ", l->intensity);
		print_col("color", l->color);
		printf("\n");
		idx++;
		l = l->next;
	}

	idx = 0;
	obj = scene->objects;
	while (obj)
	{
		printf("Obj %d: %s", idx, obj_type_str(obj->type));
		if (!obj->obj)
		{
			printf(" (null)\n");
			idx++;
			obj = obj->next;
			continue ;
		}
		if (obj->type == OBJ_SPHERE)
		{
			t_sphere *s = (t_sphere *)obj->obj;
			printf(" ");
			print_vec("center", s->center);
			printf(" radius=%.2f ", s->radius);
			print_col("color", s->mat.color);
			printf(" shininess=%.2f\n", s->mat.shininess);
		}
		else if (obj->type == OBJ_PLANE)
		{
			t_plane *p = (t_plane *)obj->obj;
			printf(" ");
			print_vec("point", p->point);
			printf(" ");
			print_vec("normal", p->normal);
			printf(" ");
			print_col("color", p->mat.color);
			printf(" shininess=%.2f\n", p->mat.shininess);
		}
		else if (obj->type == OBJ_CYLINDER)
		{
			t_cylinder *c = (t_cylinder *)obj->obj;
			printf(" ");
			print_vec("base", c->base);
			printf(" ");
			print_vec("axis", c->axis);
			printf(" radius=%.2f height=%.2f ", c->radius, c->height);
			print_col("color", c->mat.color);
			printf(" shininess=%.2f\n", c->mat.shininess);
		}
		else if (obj->type == OBJ_CONE)
		{
			t_cone *cn = (t_cone *)obj->obj;
			printf(" ");
			print_vec("apex", cn->apex);
			printf(" ");
			print_vec("axis", cn->axis);
			printf(" angle=%.2f height=%.2f ", cn->angle, cn->height);
			print_col("color", cn->mat.color);
			printf(" shininess=%.2f\n", cn->mat.shininess);
		}
		else
			printf("\n");
		idx++;
		obj = obj->next;
	}
}