#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_vec				point_normal(t_object *obj, t_vec intersection, t_ray ray)
{
	t_vec	normal;

	if (obj->type == PLANE)
		normal = obj->dir;
	if (obj->type == SPHERE)
		normal = sphere_normal(obj->pos, intersection);
	/*if (obj->type == CYLINDER)
		normal = cyl_normal(obj->shape->cyl.bottom,
				obj->shape->cyl.top, intersection);
	if (obj->type == CONE)
		normal = cone_normal(obj->shape->cone, intersection);*/
	if (vec_dot(ray.dir, normal) > 0)
		normal = vec_opposite(normal);
	return (normal);
}

t_vec		point_ray_intersect(double t, t_ray ray)
{
	t_vec	coord;

	coord = vec_scalar(ray.dir, t) + ray.origin;
	return (coord);
}

t_vec		sphere_normal(t_vec center, t_vec point)
{
	t_vec	ret;

	ret = point - center;
	vec_norm(ret);
	return (ret);
}

/*t_vec		cyl_normal(t_vec bottom, t_vec top, t_vec point)
{
	t_vec	ret;
	t_vec	axis;
	t_vec	pt_dir;
	t_vec	bot_dir;

	bot_dir = from_to(point, bottom);
	axis = vec3_normalize(from_to(bottom, top));
	pt_dir = from_to(bottom, point);
	pt_dir = mat3_mult_vec3(rot_around_vec(axis, M_PI), pt_dir);
	pt_dir = vec3_add(bottom, pt_dir);
	ret = vec3_normalize(from_to(pt_dir, point));
	return (ret);
}

t_vec		cone_normal(t_object cone, t_vec point)
{
	t_vec	ret;
	t_vec	v;
	t_vec	ap;

	v = vec3_normalize(from_to(c.bottom, c.apex));
	ap = from_to(c.apex, point);
	ret = scaling(v, ((1 + pow(tan(c.angle), 2)) * vec_dot(vec3_opposite(ap), v)));
	ret = vec3_add(ap, ret);
	ret = vec3_normalize(ret);
	return (ret);
}*/
