#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_paraboloid(t_ray *ray, t_object *obj, t_float *t)
{
	double	abc[3];
	double  a[5];
	double	xv;
	double	dv;
	t_vec	x;
	int		ret;

	//o->in = INFINITY;
	//o->out = INFINITY;
	x = ray->origin;
	xv = vec_dot(x, obj->dir);
	dv = vec_dot(ray->dir, obj->dir);
	abc[2] = vec_dot(ray->dir, ray->dir) - dv * dv;
	abc[1] = 2 * (vec_dot(ray->dir, x) - dv * (xv + 2 * 1.0));
	//abc[1] = 2 * (vec3_dot(ray->dir, x) - dv * (xv + 2 * obj->scale));
	abc[0] = vec_dot(x, x) - xv * (xv + 4 * 1.0);
	//abc[0] = vec3_dot(x, x) - xv * (xv + 4 * o->scale);
	return ((*t = solve_quadra(abc)));
/*	if (!(ret = solve_quadra(a, &a[3])))
		return (INFINITY);
	o->in = a[3];
	o->out = a[4];
	if (o->in < 0 && ((o->in = o->out) || 1))
		if (o->in < 0)
			return (INFINITY);
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut));*/
}

void	paraboloid_normal(t_ray *ray, t_object *obj, t_inter *inter)
{
	inter->normal = inter->point - obj->dir * 0.05 + 1.0;
	//inter->normal = inter->point - obj->dir * obj->m + obj->scale));
}