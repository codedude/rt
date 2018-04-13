#include "types.h"
#include "rt.h"

__kernel void	light(__constant t_object *obj, __global t_ray *rays, __global t_inter *inter, int n, __global unsigned int *screen)
{
	int gid;
	int a;
	t_vec	i;

	a = 0;
	i = {0, 0, 0};
	gid = get_global_id(0);
	while (a < n)
	{
		if (obj[a].type == LIGHT_AMBIENT)
			i.x += obj[a].intensity
		a++;
	}
}

#include "../includes/rtv1.h"

double				light(t_inter it, VEC3 v, t_env *env)
{
	double			i[4];
	t_light_list	*tmp;
	RAY				r;

	i[0] = 0.0;
	tmp = env->lum;
	while (tmp)
	{
		i[3] = 1.0;
		if (tmp->type == AMBIENT)
			i[0] += tmp->intensity;
		else
		{
			i[3] = light_mid(&r, it, &tmp, env);
			if (i[3] < 0.000001)
				continue;
			if (dot(r.direction, it.normal) < 0 && it.shp->transp > 0)
				it.normal = vec3_opposite(it.normal);
			i[1] = dot(it.normal, r.direction);
			i[2] = tmp->intensity;
			i[0] += i[3] * light_specular(it, i, v, &r);
		}
		tmp = tmp->next;
	}
	return (i[0]);
}

double					light_mid(RAY *r, t_inter it, t_light_list **tmp,
		t_env *env)
{
	t_inter			inters;
	t_inter			transp_inter;
	RAY				rayon;
	RAY				refr_ray;

	if ((*tmp)->type == POINT)
	{
		r->direction = from_to(it.point, (*tmp)->dir);
		r->direction = vec3_normalize(r->direction);
		r->origin = it.point;
		rayon.origin = it.point;
		rayon.direction = r->direction;
		inters = closest_intersect(rayon, 0.000000001, 1.0, env->shp);
	}
	else if ((*tmp)->type == DIRECTIONAL)
	{
		r->origin = it.point;
		r->direction = vec3_normalize(vec3_opposite((*tmp)->dir));
		rayon.origin = it.point;
		rayon.direction = r->direction;
		inters = closest_intersect(rayon, 0.000000001, LONG_MAX, env->shp);
	}
	if (inters.shp)
	{
		if (inters.shp->ref_index >= 1.0 && inters.shp->transp > 0)
		{
			transp_inter = inters;
			refr_ray = refract_ray(rayon, inters);
			inters = closest_intersect(refr_ray, 0.000000001, LONG_MAX, env->shp);
			if (inters.shp)
			{
				*tmp = (*tmp)->next;
				return (0.0);
			}
			else
				return (transp_inter.shp->transp);
		}
		else
			*tmp = (*tmp)->next;
		return (0.0);
	}
	return (1.0);
}

double				light_specular(t_inter it, double i[4], VEC3 v, RAY *r)
{
	double	ret;

	ret = 0;
	if (i[1] > 0)
	{
		ret = i[2] * i[1];
	if (it.shp->s > 0)
		{
			r->direction = vec3_sub(scaling(it.normal,
						dot(it.normal, r->direction) * 2.0), r->direction);
			i[1] = dot(r->direction, v);
			if (i[1] > 0)
				ret += i[2] * pow(i[1] / (vec3_length(r->direction)
							* vec3_length(v)), it.shp->s);
		}
	}
	return (ret);
}