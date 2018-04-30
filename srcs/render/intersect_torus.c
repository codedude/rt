#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"


A = radius central;
B = radius donut; 			A > B

P = D + uE;   D = origin ray / E = dir ray / u = t


t_float		intersect_torus(t_ray *ray, t_object *obj, t_float *t)
{
	t_float	a;
	t_float	b;
	t_float	c;
	t_float	d;
	t_float	e;
	t_float	g;
	t_float	h;
	t_float	i;
	t_float	j;
	t_float	k;
	t_float	l;

	g = 4.0 * obj->radius * obj->radius * (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
	h = 8.0 * obj->radius * obj->radius * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y);
	i = 4.0 * obj->radius * obj->radius * (ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y);
	j = vec_dot(ray.dir, ray.dir);
	k = 2.0 * vec_dot(ray.origin, ray.dir);
	l = vec_dot(ray.origin, ray.origin) + (obj->radius * obj->radius - obj->radius2 * obj->radius2);

	a = j * j;
	b = 2.0 * j * k;
	c = (2.0 * j * l) + (k * k) - g;
	d = 2.0 * k * l - h;
	e = l * l - i;
}

t_vec		solve_quartic(t_float a, t_float b, t_float c, t_float d)
{

}