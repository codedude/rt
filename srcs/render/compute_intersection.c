t_inter				closest_intersect(t_ray ray, double t_min,
		double t_max, t_objects objects)
{
	double		t;
	t_shp_list	*tmp;
	t_inter		inters;
	RAY		refr_ray;

	inters.t = t_max;
	inters.shp = NULL;
	tmp = shp;
	while (tmp != NULL)
	{
		t = inter(ray, tmp);
		if (t < inters.t && t > t_min && t < t_max)
		{
			inters.t = t;
			inters.shp = tmp;
		}
		tmp = tmp->next;
	}
	if (inters.shp)
	{
		inters.point = point_ray_intersect(inters.t, ray);
		inters.normal = point_normal(inters.shp, inters.point, ray);
	}
	return (inters);
}