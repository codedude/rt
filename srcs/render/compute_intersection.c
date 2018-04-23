#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_inter				closest_intersect(t_ray ray, t_float t_min,
		t_float t_max, t_objects *objects)
{
	t_float		t;
	t_inter		inter;
	int 		i;

	inter.t = t_max;
	inter.id = -1;
	i = 0;
	while (i < objects.size)
	{
		t = inters(ray, objects.objects_array[i]);
		if (t < inter.t && t > t_min && t < t_max)
		{
			inter.t = t;
			inter.id = i;
		}
		i++;;
	}
	if (inter.id >= 0)
	{
		inter.point = point_ray_intersect(inters.t, ray);
		inter.normal = point_normal(objects.object_array[inter.id], inter.point, ray);
	}
	return (inter);
}

t_float	inters(t_ray ray, t_object obj)
{
	t_float	t;

	t = 0;
	if (obj>type == SPHERE)
		t = r_inter_sphere(ray, obj);
	if (obj->type == PLAN)
		t = r_inter_plan(ray, obj);
	if (obj->type == CYLINDER)
		t = r_inter_cylindre(ray, obj);
	if (obj->type == CONE)
		t = r_inter_cone(ray, obj);
	return (t);
}

t_float	r_inter_plan(t_ray ray, t_object plan)
{
	t_float	t;
	t_float	denom;

	denom = dot(ray.dir, plan.dir);
	if (denom < 0.000001 && denom > -0.000001)
		return (0);
	t = -dot(vec3_sub(ray.origin, plan.pos), plan.dir);
	t = t / denom;
	return (t);
}

t_float	r_inter_sphere(t_ray ray, t_object obj)
{
	t_float	t[2];
	t_vec	k;
	t_float	delta;
	t_vec	d;
	t_vec	co;

	d = ray.dir;
	co = from_to(obj.pos, ray.origin);
	k.x = dot(d, d);
	k.y = 2.0 * dot(co, d);
	k.z = dot(co, co) - (obj.radius * obj.radius);
	delta = sqrt(k.y * k.y - 4.0 * k.x * k.z);
	if (isnan(delta))
		return (-1);
	t.x = (-k.y + delta) / (2.0 * k.x);
	t.y = (-k.y - delta) / (2.0 * k.x);
	if (t.x < 0.00000001 || t.y < 0.00000001)
		return (fmax(t.x, t.y));
	return (fmin(t.x, t.y));
}