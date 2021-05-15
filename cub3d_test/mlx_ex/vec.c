#include "mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

t_vec	vec_new(double x, double y)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vec	vec_mul(t_vec a, double b)
{
	a.x *= b;
	a.y *= b;
	return (a);
}

// t_vec	equation_solver(t_vec *coeff0, t_vec *coeff1, t_vec *constant)
// {
// 	t_vec	result;
// 	double	det;

// 	det = coeff0->x * coeff1->y - coeff1->x * coeff0->y;
// 	result.x = (coeff1->y * constant->x + coeff1->x)
// }

t_vec	vec_rot_min_ccw(t_vec a, double angle)
{
	double	sin_angle;
	double	cos_angle;
	t_vec	result;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	result.x = cos_angle * a.x - sin_angle * a.y;
	result.y = sin_angle * a.x - cos_angle * a.y;
	return (result);
}

int		main(void)
{
	t_vec	a;
	t_vec	b;

	a = vec_new(4, 3);
	b = vec_new(2, 5);

	a = vec_add(a, b);
	printf("[%.f],[%.f]\n", a.x, a.y);
	return (0);
}
