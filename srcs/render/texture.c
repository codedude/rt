#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_vec		texture_color(t_inter inter)
{
	t_vec	color;
	t_vec	px;
	int 	coord;

	px = uv_mapping(inter);
	printf("ici1");
	coord = uv_to_texture_coord(px, inter.obj->texture);
	printf("ici");
	color = get_text_color(inter.obj->texture.pixels, coord);
	printf("ici3");
	return (color);
}

t_vec		uv_mapping(t_inter inter)
{
	t_vec ret;

	ret = VEC_INIT(0.0, 0.0, 0.0);
	//if (inter.obj->type == PLANE)
	//	ret = map_plane(inter.obj_coord);
	if (inter.obj->type == SPHERE)
		ret = map_sphere(inter.obj_coord);
/*	else if (inter.obj->type == CYLINDER)
		ret = map_cylinder(inter.obj_coord);
	else if (inter.obj->type == CONE)
		ret = map_cone(inter.obj_coord);
	else if (inter.obj->type == PARABOLOID)
		ret = map_paraboloid(inter.obj_coord);
	else if (inter.obj->type == HYPERBOLOID)
		ret = map_hyperboloid(inter);
	else if (inter.obj->type == CUBE)
		ret = map_cube(inter.obj_coord);*/
	return (ret);
}

int 		uv_to_texture_coord(t_vec px, t_obj_text t)
{
	int coord;
	int u;
	int v;
	u = (int)((t_float)t.width * px.x);
	v = (int)((t_float)t.height * px.y);
/*	if (t.off > 0)
	{
		u += t.off;
		u = u % t.width;
		v += t.off / width;
	}*/
	coord = u + v * t.width;
	return (coord);
}

t_vec 		get_text_color(t_color *pixels, int coord)
{
	return (color_to_vec(pixels[coord]));
}
