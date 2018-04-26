#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_ray				reflected_ray(t_inter inter, t_vec ray)
{
	t_ray	ret;

	ret.origin = inter.point;
	ret.dir = inter.normal * (2 * vec_dot(inter.normal, ray));
	ret.dir = ret.dir - ray;
	return (ret);
}

t_vec				reflexion(t_rt *rt, t_hit *hit, int depth, t_vec color)
{
	t_vec	reflected_color;
	t_hit 	reflect;

	reflected_color = VEC_ZERO;
	if (hit->inter.obj->reflexion > 0 && depth > 0)
	{
		reflect.ray = reflected_ray(hit->inter, (-1) * hit->ray.dir);
		reflect.ray.refraction = hit->ray.refraction;
		reflected_color = compute_color(rt, &reflect, depth - 1);
	}
	return (reflected_color);
}