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
	px = uv_to_texture_coord(px, inter.obj->texture);
	color = rgb_to_vec(inter.obj->texture.pixel[px.x][px.y]);
}

t_vec	uv_mappging(t_inter inter)
{
	t_vec ret;

	ret = VEC_INIT(0.0, 0.0, 0.0);
	if (inter->obj->type == PLANE)
		ret = map_plane(inter.obj_coord);
	else if (inter->obj->type == SPHERE)
		ret = map_sphere(inter.obj_coord);
	else if (inter->obj->type == CYLINDER)
		ret = map_cylinder(inter.obj_coord);
	else if (inter->obj->type == CONE)
		ret = map_cone(inter.obj_coord);
	else if (inter->obj->type == PARABOLOID)
		ret = map_paraboloid(inter.obj_coord);
	else if (inter->obj->type == HYPERBOLOID)
		ret = map_hyperboloid(inter);
	else if (inter->obj->type == CUBE)
		ret = map_cube(inter.obj_coord);
	return (ret);
}

t_vec 	uv_to_texture_coord(t_vec px, t_texture t)
{
	
}