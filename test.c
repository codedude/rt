
#include <stdio.h>
#include <stdlib.h>

typedef double			t_float;
typedef double			t_vec __attribute__((ext_vector_type(4),aligned(32)));

void	test(t_vec *v)
{
	*v *= -1.0;
}

int	main(void)
{
	t_vec	v;

	v = (t_vec){2.0, 2.0, 2.0};
	test(&v);
	v += v;
	printf("%lf, %lf, %lf\n", v[0], v.y, v.z);
	return (0);
}
