#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_vec		color_perturbation(t_inter inter)
{
	t_float		t;
	t_float		v[3];
	t_vec		color;

	color = inter.obj->color;
	color = chess(inter);
	/*if (inter.obj->perturbation == MARBLE)
	{
		v[0] = inter.point.x;
		v[1] = inter.point.y;
		v[2] = inter.point.z;
		t = noise3(v);
		color = marble(t, inter);
	}*/
	return (color);
}

t_vec		chess(t_inter inter)
{

	if ((inter.point.x < 0 && inter.point.y < 0) || (inter.point.x > 0 && inter.point.y > 0))
        {    
            if ((int)fabs(inter.point.x) % 10 < 5 && ((int)fabs(inter.point.y) % 10 < 5))
                return (VEC_INIT(0.0, 0.0, 0.0));
            if (!((int)fabs(inter.point.x) % 10 < 5 || ((int)fabs(inter.point.y) % 10 < 5)))
                return(VEC_INIT(0.0, 0.0, 0.0));
        }
        if ((inter.point.x > 0 && inter.point.y < 0) || (inter.point.x < 0 && inter.point.y > 0))
        {
            if ((int)fabs(inter.point.x) % 10 >= 5 && ((int)fabs(inter.point.y) % 10 < 5))
                return (VEC_INIT(0.0, 0.0, 0.0));
            if ((int)fabs(inter.point.x) % 10 < 5 && ((int)fabs(inter.point.y) % 10 >= 5))
                return(VEC_INIT(0.0, 0.0, 0.0));
        }
    return (inter.obj->color);
}

t_vec		marble(t_float t, t_inter inter)
{
	t_float x;
	t_vec color;

	x = 0.0;
  	color = VEC_INIT(0.0, 0.0, 0.0);
  	x = sin(inter.point[0] + cos(inter.point[1] + 8.0 * t * M_PI) + 6.0 * t * M_PI);
 	x = sqrt(x+1) * 0.7071;
 	color.y = (0.7 + 0.7 * x) * inter.obj->color.y;
  	x = sqrt(x);
  	color.x = (0.7 + 0.3 * x) * inter.obj->color.x;
  	color.z = (0.3 + 0.8 * x) * inter.obj->color.z;


  	/*x = sin(inter.point[0] + 3.0 * t * M_PI);
 	x = sqrt(x+1) * 0.7071;
 	color.y = (0.7 + 0.7 * x) * inter.obj->color.y;
  	x = sqrt(x);
  	color.x = (0.7 + 0.3 * x) * inter.obj->color.x;
  	color.z = (0.3 + 0.8 * x) * inter.obj->color.z;*/

  	return(color);
}

t_vec		normal_perturbation(t_vec	normal)
{
	t_vec	tmp;
	t_vec	ret;
	t_float	v[3];
	t_float x;
	t_float t;

//	x = sin(normal[0] + cos(normal[1] + 8.0 * t * M_PI) + 6.0 * t * M_PI);
 //	x = sqrt(x+1) * 0.7071;
	v[0] = normal.x + 0.2;
	v[1] = normal.y;
	v[2] = normal.z;
	//t = noise3(v);
	//x = sin(normal[0] + cos(normal[1] + 8.0 * t * M_PI) + 6.0 * t * M_PI);
 	//x = sqrt(x+1) * 0.7071;
	tmp.x = noise3(v);
	v[0] = normal.x - 0.4;
	tmp.x = noise3(v) - tmp.x;
	v[0] += 0.2;

	v[1] = normal.y + 0.2;
	tmp.y = noise3(v);
	v[1] = normal.y - 0.4;
	tmp.y = noise3(v) - tmp.y;
	v[1] += 0.2;

	v[2] = normal.z + 0.2;
	tmp.z = noise3(v);
	v[2] = normal.z - 0.4;
	tmp.z = noise3(v) - tmp.z;
	v[2] += 0.2;

	ret = tmp + normal;
	return (ret);
}