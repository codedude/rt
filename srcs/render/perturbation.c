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
//	t_float		t;
//	t_float		v[3];
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

/*	if ((inter.point.x < 0 && inter.point.y < 0) || (inter.point.x > 0 && inter.point.y > 0))
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
*/
    if ((inter.point.x * inter.point.z / inter.point.y  < 0 && inter.point.z < 0) || (inter.point.x * inter.point.z / inter.point.y  > 0 && inter.point.z > 0))
        {
            if ((int)fabs(inter.point.x * inter.point.z / inter.point.y) % 10 < 5 && ((int)fabs(inter.point.z)) % 10 < 5)
                return (VEC_INIT(0.0, 0.0, 0.0));
            if (!((int)fabs(inter.point.x * inter.point.z / inter.point.y) % 10 < 5 || ((int)fabs(inter.point.z)) % 10 < 5))
                return(VEC_INIT(0.0, 0.0, 0.0));
        }
        if ((inter.point.x * inter.point.z / inter.point.y > 0 && inter.point.z < 0) || (inter.point.x * inter.point.z / inter.point.y < 0 && inter.point.z > 0))
        {
            if ((int)fabs(inter.point.x * inter.point.z / inter.point.y) % 10 >= 5 && ((int)fabs(inter.point.z)) % 10 < 5)
                return (VEC_INIT(0.0, 0.0, 0.0));
            if ((int)fabs(inter.point.x * inter.point.z / inter.point.y) % 10 < 5 && ((int)fabs(inter.point.z)) % 10 >= 5)
                return(VEC_INIT(0.0, 0.0, 0.0));
        }
        return (inter.obj->color);
}

t_vec		marble1(t_float t, t_inter inter)
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
  	return(color);
}

t_vec		marble2(t_float t, t_inter inter)
{
	t_float x;
	t_vec color;

  	x = sin(inter.point[0] + 3.0 * t * M_PI);
 	x = sqrt(x+1) * 0.7071;
 	color.y = (0.7 + 0.7 * x) * inter.obj->color.y;
  	x = sqrt(x);
  	color.x = (0.7 + 0.3 * x) * inter.obj->color.x;
  	color.z = (0.3 + 0.8 * x) * inter.obj->color.z;
  	  	return(color);
}

t_vec		normal_perturbation(t_inter	inter) // water effect for horizontal plan
{
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec	ret;
	t_float	v[3];
	t_float	epsi;

	epsi = 1.0;
	v[0] = inter.normal.x + inter.point.x + epsi;
	v[1] = inter.normal.y * 50 + 100 * inter.point.y;
	v[2] = inter.normal.z + inter.point.z;
	tmp1.x = noise3(v);
	v[0] = inter.normal.x + inter.point.x - epsi;
	tmp2.x = noise3(v);

	v[0] = inter.normal.x + inter.point.x; 
	v[1] = inter.normal.y * 50 + 100 * inter.point.y + epsi;
	tmp1.y = noise3(v);
	v[1] = inter.normal.y * 50 + 100 * inter.point.y - epsi;
	tmp2.y = noise3(v);
	
	v[1] = inter.normal.y * 50 + 100 * inter.point.y;
	v[2] = inter.normal.z + inter.point.z + epsi;
	tmp1.z = noise3(v);
	v[2] = inter.normal.z + inter.point.z - epsi;
	tmp2.z = noise3(v);

	tmp1 = tmp2 - tmp1;
	ret = tmp1 + inter.normal;
	return (ret);
}
