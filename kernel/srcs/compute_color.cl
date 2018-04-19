#include "types.h"
#include "rt.h"


__kernel void	compute_color(__global t_inter *inters, __global t_vec *intensity, __global unsigned int *screen)

{
	int gid;
	gid = get_global_id(0);

	screen[gid] = get_color(inters[gid].color * intensity[gid]);
}

unsigned int	get_color(t_vec color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	c;

	b = (unsigned int)(color.z * 255.0);
	g = (unsigned int)(color.y * 255.0);
	r = (unsigned int)(color.x * 255.0);

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}