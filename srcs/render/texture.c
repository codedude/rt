#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_vec	texture_color(t_inter inter)
{
	t_vec	color;
	t_vec	px;

	px = uv_mapping();
	px = uv_to_texture_coord();
	color = inter.obj->texture.pixel
}

t_vec	uv_mappging(t_inter inter)
{
	t_vec ret;

	ret = VEC_INIT(0.0, 0.0, 0.0);
	if (inter->obj->type == PLANE)
		ret = map_plane(inter);
	else if (inter->obj->type == SPHERE)
		ret = map_sphere(inter);
	else if (inter->obj->type == CYLINDER)
		ret = map_cylinder(inter);
	else if (inter->obj->type == CONE)
		ret = map_cone(inter);
	else if (inter->obj->type == PARABOLOID)
		ret = map_paraboloid(inter);
	else if (inter->obj->type == HYPERBOLOID)
		ret = map_hyperboloid(inter);
	else if (inter->obj->type == CUBE)
		ret = map_cube(inter);
	return (ret);
}