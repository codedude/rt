#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "libft.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

int				closest_intersect(t_ray ray, 
		t_float t_max, t_objects objects, t_inter *inter)
{
	t_float		t;
	int 		i;

	inter->t = t_max;
	inter->obj = NULL;
	i = 0;
	while (i < objects.size)
	{
		t = inters(ray, &objects.objects_array[i]);
		if (t < inter->t && t > 0.00001 && t < t_max)
		{
			inter->t = t;
			inter->obj = &objects.objects_array[i];
		}
		i++;;
	}
	if (inter->obj != NULL)
	{
		inter->point = point_ray_intersect(inter->t, ray);
		inter->normal = point_normal(inter->obj, inter->point, ray);
	}
	return (SUCCESS);
}

t_float	inters(t_ray ray, t_object *obj)
{
	t_float	t;

	t = 0;
	if (obj->type == SPHERE)
		t = r_inter_sphere(ray, obj);
	if (obj->type == PLANE)
		t = r_inter_plan(ray, obj);
/*	if (obj->type == CYLINDER)
		t = r_inter_cylindre(ray, obj);
	if (obj->type == CONE)
		t = r_inter_cone(ray, obj);*/
	return (t);
}

t_float	r_inter_plan(t_ray ray, t_object *plan)
{
	t_float	t;
	t_float	denom;

	denom = vec_dot(ray.dir, plan->dir);
	if (denom < 0.000001 && denom > -0.000001)
		return (0);
	t = -vec_dot(ray.origin - plan->pos, plan->dir);
	t = t / denom;
	return (t);
}

t_float	r_inter_sphere(t_ray ray, t_object *obj)
{
	t_float	t[2];
	t_vec	k;
	t_float	delta;
	t_vec	d;
	t_vec	co;

	d = ray.dir;
	co = ray.origin - obj->pos;
	k[0] = vec_dot(d, d);
	k[1] = 2.0 * vec_dot(co, d);
	k[2] = vec_dot(co, co) - (obj->radius * obj->radius);
	delta = sqrt(k[1] * k[1] - 4.0 * k[0] * k[2]);
	if (isnan(delta))
		return (-1);
	t[0] = (-k[1] + delta) / (2.0 * k[0]);
	t[1] = (-k[1] - delta) / (2.0 * k[0]);
	if (t[0] < 0.00000001 || t[1] < 0.00000001)
		return (fmax(t[0], t[1]));
	return (fmin(t[0], t[1]));
}
