#include "types.h"
#include "rt.h"

t_float		is_there_inter(t_ray ray, float t_min, float t_max, __constant t_object *obj, int n)
{
	int 	i;
	t_float	t;

	i = 0;
	while (i < n)
	{
		t = inters(ray, obj[i]);
		if (t < interi->t && t > t_min && t < t_max
			&& obj[i].type != LIGHT_AMBIENT 
			&& obj[i].type != LIGHT_POINT 
			&& obj[i].type != LIGHT_SPOT 
			&& obj[i].type != LIGHT_PAR)
		{
			return (1.0 - obj[i].transparency)
		}
		i++;
	}
}


t_float inters(__private t_ray ray, __private t_object obj)
{

	t_float	t;

	t = 0;
	if (obj.type == SPHERE)
		t = r_inter_sphere(ray, obj);
	else if (obj.type == PLANE)
		t = r_inter_plan(ray, obj);
/*	else if (obj.type == CYLINDER)
		t = r_inter_cylinder(ray, obj);
	else if (obj.type == CONE)
		t = r_inter_cone(ray, obj);*/
	return (t);
}

t_float	r_inter_plan(__private t_ray ray, __private t_object plan)
{
	t_float	t;
	t_float	denom;

	denom = dot(ray.dir, plan.dir);
	if (denom < 0.000001 && denom > -0.000001)
		return (0);
	t = -dot((ray.origin - plan.pos), plan.dir);
	t = t / denom;
	return (t);
}

t_float	r_inter_sphere(t_ray ray, t_object sphere)
{
	__float2	t;
	t_vec	k;
	t_vec	d;
	t_vec	co;

	d = ray.dir;
	co = ray.origin - sphere.pos;
	k.x = dot(d, d);
	k.y = 2.0 * dot(co, d);
	k.z = dot(co, co) - (sphere.radius * sphere.radius);
	t = quadratic(k.x, k.y, k.z);
	if (t.x < 0.00000001 || t.y < 0.00000001)
		return (fmax(t.x, t.y));
	return (fmin(t.x, t.y));
}
/*
t_float	r_inter_cylinder(t_ray ray, t_object cylinder)
{
	__float2	t;
	t_vec	k;
	t_vec	v[3];

	v[0] = normalize(cylinder.top - cylinder.bottom);
	v[1] = (v[0] * dot(v[0], ray.dir)) - ray.dir;
	v[2] = ray.origin - cylinder.bottom;
	k.x = dot(v[1], v[1]);
	k.y = 2.0 * dot(v[1], ((v[0] * dot(v[0], v[2])) - v[2]));
	v[1] = (v[0] * dot(v[0], v[2])) - v[2];
	k.z = dot(v[1], v[1]) - (cylinder.r * cylinder.r);
	t = quadratic(k.x, k.y, k.z);
	return (r_inter_cyl2(ray, cylinder, v[0], t));
}

t_float	r_inter_cyl2(t_ray ray, t_object cylinder, t_vec axis, __float2 t)
{
	t_float	test1;
	t_float	test2;
	t_vec	tmp;

	tmp = ray.origin + ray.dir * t.x;
	test1 = dot(axis, tmp - cylinder.bottom);
	test2 = dot(axis, tmp - cylinder.top);
	if (test1 < 0.0000001 || test2 >= 0.0000001)
		t.x = -1.;
	tmp = ray.origin + ray.dir * t.y;
	test1 = dot(axis, cylinder.bottom - tmp);
	test2 = dot(axis, cylinder.top - tmp);
	if (test1 <= 0.0000001 || test2 >= 0.0000001)
		t.y = -1.;
	if (t.x <= 0.0000001 && t.y <= 0.0000001)
		return (-1.);
	if (t.x <= 0.0000001 || t.y <= 0.0000001)
		return (fmax(t.x, t.y));
	return (fmin(t.x, t.y));
}

t_float	r_inter_cone(t_ray ray, t_object cone)
{
	__float2	t;
	t_float	k[6];
	t_vec	v[4];

	v[0] = normalize(cylinder.top - cylinder.bottom);
	v[3] = ray.origin - cylinder.apex;
	v[1] = ray.dir - v[0] * dot(v[0], ray.dir);
	v[2] = v[3] - v[0] * dot(v[0], v[3]);
	k[4] = dot(ray.dir, v[0]);
	k[5] = dot(v[3], v[0]);
	k[0] = pown(cos(cylinder.angle), 2) * dot(v[1], v[1]) -
		pown(sin(cylinder.angle), 2) * k[4] * k[4];
	k[1] = 2.0 * pown(cos(cylinder.angle), 2) * dot(v[1], v[2]) - 2.0 *
		pown(sin(cylinder.angle), 2) * k[4] * k[5];
	k[2] = pown(cos(cylinder.angle), 2) * dot(v[2], v[2]) -
		pown(sin(cylinder.angle), 2) * pown(k[5], 2);
	t = quadratic(k[0], k[1], k[2]);
	return (r_inter_cone2(ray, cylinder, v[0], t));
}

t_float	r_inter_cone2(t_ray ray, t_object cone, t_vec axis, __float2 t)
{
	t_float	test1;
	t_float	test2;
	t_vec	tmp;

	tmp = ray.origin + ray.dir * t.x;
	test1 = dot(axis, tmp - cylinder.bottom);
	test2 = dot(axis, tmp - cylinder.top);
	if (test1 <= 0.0000001 || test2 >= 0.0000001)
		t.x = -1.;
	tmp = ray.origin + ray.dir * t.y;
	test1 = dot(axis, tmp - cylinder.bottom);
	test2 = dot(axis, tmp - cylinder.top);
	if (test1 <= 0.0000001 || test2 >= 0.00000001)
		t.y = -1.;
	if (t.x <= 0.00000001 && t.y <= 0.0000001)
		return (-1.);
	if (t.x <= 0.0000001 || t.y <= 0.00000001)
		return (fmax(t.x, t.y));
	return (fmin(t.x, t.y));
}
*/
__float2	quadratic(t_float a, t_float b, t_float c)
{
	t_float		delta;
	__float2	ret;

	delta = sqrt(b * b - 4.0 * a * c);
	if (isnan(delta))
	{
		ret.x = 0;
		ret.y = 0;
		return (ret);
	}
	ret.x = (-b + delta) / (2.0 * a);
	ret.y = (-b - delta) / (2.0 * a);
	return (ret);
}


__kernel void	light(__constant t_object *obj, __global t_ray *rays, __global t_ray *light_ray, __global t_inter *inter,
						__global t_vec *intensity, int n)
{
	int gid;
	int a;
	t_vec	i;
	t_ray	ray_tmp;
	t_float	transp;

	a = 0;
	i = {0, 0, 0};
	gid = get_global_id(0);
	while (a < n)
	{
		if (obj[a].type == LIGHT_AMBIENT)
			intensity[gid] += obj[a].intensity * obj.phong[PHONG_KA];
		else
			if (obj[a].type == LIGHT_POINT)
			{
				ray_tmp.dir = normalize(obj[a].pos - inter[gid].point);
				ray_tmp.origin = inter[gid].point;
				ray_tmp.refraction = inter[gid].refraction;
				light_ray[gid] = ray_tmp;
				intensity[gid] += obj[a].intensity * obj.phong[PHONG_KD];
			}
			else if (obj[a].type == LIGHT_PAR)
			{
				ray_tmp.dir = obj[a].dir;
				ray_tmp.origin = inter[gid].point;
				ray_tmp.refraction = inter[gid].refraction;
				light_ray[gid] = ray_tmp;
				intensity[gid] += obj[a].intensity * obj.phong[PHONG_KD];
			}

		}
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