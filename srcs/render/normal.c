t_vec				point_normal(t_object obj, t_vec intersection, t_ray ray)
{
	t_vec	normal;

	normal = new_vec3(0.0, 0.0, 0.0);
	if (obj->type == PLAN)
		normal = vec3_normalize(obj.dir);
	if (obj->type == SPHERE)
		normal = sphere_normal(obj.pos, intersection);
	/*if (obj->type == CYLINDRE)
		normal = cyl_normal(obj->shape->cyl.bottom,
				obj->shape->cyl.top, intersection);
	if (obj->type == CONE)
		normal = cone_normal(obj->shape->cone, intersection);*/
	if (dot(ray.dir, normal) > 0)
		normal = vec3_opposite(normal);
	return (normal);
}

t_vec		point_ray_intersect(double t, t_ray ray)
{
	t_vec	coord;

	coord = scaling(ray.direction, t);
	coord = vec3_add(coord, ray.origin);
	return (coord);
}

t_vec		sphere_normal(t_vec center, t_vec point)
{
	t_vec	ret;

	ret = from_to(center, point);
	ret = vec3_normalize(ret);
	return (ret);
}

t_vec		cyl_normal(t_vec bottom, t_vec top, t_vec point)
{
	t_vec	ret;
	t_vec	axis;
	t_vec	pt_dir;
	t_vec	bot_dir;

	bot_dir = from_to(point, bottom);
	axis = vec3_normalize(from_to(bottom, top));
	pt_dir = from_to(bottom, point);
	pt_dir = mat3_mult_vec3(rot_around_vec(axis, M_PI), pt_dir);
	pt_dir = vec3_add(bottom, pt_dir);
	ret = vec3_normalize(from_to(pt_dir, point));
	return (ret);
}

t_vec		cone_normal(t_cone c, t_vec point)
{
	t_vec	ret;
	t_vec	v;
	t_vec	ap;

	v = vec3_normalize(from_to(c.bottom, c.apex));
	ap = from_to(c.apex, point);
	ret = scaling(v, ((1 + pow(tan(c.angle), 2)) * dot(vec3_opposite(ap), v)));
	ret = vec3_add(ap, ret);
	ret = vec3_normalize(ret);
	return (ret);
}