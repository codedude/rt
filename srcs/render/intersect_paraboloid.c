#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_paraboloid(t_ray *ray, t_object *obj, t_float *t)
{
	double	abc[3];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	abc[1] = 2.0 * (ray->origin.x * ray->dir.x + ray->dir.z * ray->origin.z) - obj->radius * ray->dir.y;
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - obj->radius * ray->origin.y;
	return ((*t = solve_quadra(abc)));
}

void	norm_paraboloid(t_ray *ray, t_object *obj, t_inter *inter)
{
//	inter->normal = inter->point - obj->dir * 0.05 + 1.0;
	//inter->normal = inter->point - obj->dir * obj->m + obj->scale));
	inter->normal = vec_norm(VEC_INIT(inter->obj_coord.x, (-1) * inter->obj->radius, inter->obj_coord.z));
}