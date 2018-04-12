/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.cl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:30:15 by vparis            #+#    #+#             */
/*   Updated: 2018/04/11 18:30:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

__kernel void intersect(__constant t_object *obj, __constant t_ray *rays, __global t_inter *inter, int n)
{
	int		gid;

	gid = get_global_id(0);
	inter[gid] = closest_inter(ray[gid], t_min, t_max, inter, n);
}

t_inter		closest_inter(t_ray *ray, float t_min, float t_max, __constant t_object *obj, int n);
{
	private int 	i;
	private float	t;
	private t_inter inter;

	i = 0;
	inter.t = t_max;
	inter.id = -1;
	while (i < n)
	{
		t = inter(ray, obj[i]);
		if (t < inter.t && t > t_min && t < t_max
			&& obj[i].type != LIGHT_AMBIENT 
			&& obj[i].type != LIGHT_POINT 
			&& obj[i].type != LIGHT_SPOT 
			&& obj[i].type != LIGHT_PAR)
		{
			inter.t = t;
			inter.id = i;
			inter.color = obj[i].color;
		}
		i++;
	}
	if (inter.id > -1)
	{
		inter.point = (inter.t * ray.dir) + ray.origin;
		inter.normal = compute_normal(inter.point, obj[inter.id]);
	}
	return (inter);
}


__float inter(__private t_ray ray, __private t_object obj)
{

	__float	t;

	t = 0;
	if (obj.type == SPHERE)
		t = r_inter_sphere(ray, obj);
	else if (obj.type == PLANE)
		t = r_inter_plan(ray, obj);
	else if (obj.type == CYLINDER)
		t = r_inter_cylindre(ray, obj);
	else if (obj.type == CONE)
		t = r_inter_cone(ray, obj);
	return (t);
}

__float	r_inter_plan(__private t_ray ray, __private t_object plan)
{
	__float	t;
	__float	denom;

	denom = dot(ray.dir, plan.dir);
	if (denom < 0.000001 && denom > -0.000001)
		return (0);
	t = -dot((ray.origin - plan.origin), plan.dir);
	t = t / denom;
	return (t);
}

__float	r_inter_sphere(t_ray ray, t_object sphere)
{
	__float2	t;
	__float3	k;
	__float3	d;
	__float3	co;

	d = ray.dir;
	co = ray.origin - obj.pos;
	k.x = dot(d, d);
	k.y = 2.0 * dot(co, d);
	k.z = dot(co, co) - (obj.radius * obj.radius);
	t = quadratic(k.x, k.y, k.z);
	if (t.x < 0.00000001 || t.y < 0.00000001)
		return (fmax(t.x, t.y));
	return (fmin(t.x, t.y));
}

__float	r_inter_cylinder(t_ray ray, t_object cylinder)
{
	__float2	t;
	__float3	k;
	__float3	v[3];

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

__float	r_inter_cyl2(t_ray ray, t_object cylinder, __float3 axis, __float2 t)
{
	__float	test1;
	__float	test2;
	__float3	tmp;

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

__float	r_inter_cone(t_ray ray, t_object cone)
{
	__float2	t;
	__float	k[6];
	__float3	v[4];

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

__float	r_inter_cone2(t_ray ray, t_object cone, __float3 axis, __float2 t)
{
	__float	test1;
	__float	test2;
	__float3	tmp;

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

__float2	quadratic(t_float a, t_float b, t_float c)
{
	t_float		delta;
	__float2	ret;

	delta = sqrt(b * b - 4.0 * a * c);
	if (isnan(delta))
		return (ret{{nan(0), nan(0)}})
	ret.x = (-b + delta) / (2.0 * a);
	ret.y = (-b - delta) / (2.0 * a);
	return (ret);
}
