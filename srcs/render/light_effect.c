#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_uint		reflect(t_ray ray, t_rt *rt, int depth, t_inter inter)
{
	t_uint	reflected_color;
	t_ray refl_ray;

	reflected_color = 0;
	if (depth > 0)
	{
		refl_ray = reflected_ray(inter, vec3_opposite(ray.dir));
		refl_ray.ref_index = ray.ref_index;
		reflected_color = rt(refl_ray, depth - 1, env);
	}
	return (reflected_color);
}

t_ray				reflected_ray(t_inter inter, t_vec ray)
{
	t_ray	ret;

	ret.origin = inter.point;
	ret.dir = scaling(inter.normal, 2 * dot(inter.normal, ray));
	ret.dir = vec3_sub(ret.dir, ray);
	return (ret);
}

t_uint		refract(t_ray ray, t_env *env, int depth, t_inter inter)
{
	t_uint	refracted_color;
	t_ray refracted_ray;

	refracted_color = 0;
	if (inter.shp->ref_index >= 1.0 || inter.shp->transp > 0)
	{
		refracted_ray = refract_ray(ray, inter);

		refracted_color = rt(refracted_ray, depth - 1, env);
	}
	return (refracted_color);
}

t_ray				refract_ray(t_ray ray, t_inter inter)
{
	t_float	n;
	t_float	c1;
	t_float	c2;
	t_ray	ret;

	n = ray.ref_index / inter.shp->ref_index;
	c1 = dot(vec3_opposite(vec3_normalize(ray.dir)), inter.normal);
	c2 = 1.0 - (n * n * (1.0 - (c1 * c1)));
	if (c2 < 0)
	{
		ret.origin = (VEC3){nan(0), nan(0), nan(0)};
		return (ret);
	}
	c2 = sqrt(c2);
	ret.dir = scaling(vec3_normalize(ray.dir), n);
	ret.dir = vec3_add(ret.dir, scaling(inter.normal, (n * c1 - c2)));
	ret.origin = inter.point;
	ret.ref_index = inter.shp->ref_index;
	return (ret);
}

t_float			fresnel(t_ray ray, t_inter inter)
{
	t_float	n;
	t_float	cosi;
	t_float	cost;
	t_float	sint;
	t_float	rs;
	t_float	rp;
	t_float	kr;
	t_ray	ret;

	n = ray.ref_index / inter.shp->ref_index;
	cosi = dot(vec3_opposite(vec3_normalize(ray.dir)), inter.normal);
	sint = n * sqrt(1 - cosi * cosi);
	if (sint >= 1) //total internal reflexion
		kr = 1;
	else
	{
		cost = sqrt(1 - sint * sint);
		rs = ((inter.shp->ref_index * cosi) - (ray.ref_index * cost)) / ((inter.shp->ref_index * cosi) + (ray.ref_index * cost));
		rp = ((ray.ref_index * cost) - (inter.shp->ref_index * cosi)) / ((ray.ref_index * cost) + (inter.shp->ref_index * cosi));
		kr = (rs * rs + rp * rp) / 2;
	}	
	return (kr);
}