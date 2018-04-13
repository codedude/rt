#include "types.h"
#include "rt.h"


__kernel void	intensity(__constant t_object *obj, __global t_ray *rays, __global t_ray *light_ray, __global t_inter *inter,
						__global t_vec *intensity, int n)