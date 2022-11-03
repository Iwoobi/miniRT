/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_sp_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:02:16 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 16:07:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	check_hit_gray_sp_d(double *d, double *dot, t_mlx *mlx)
{
	double	exist;
	double	a[3];
	double	t;
	double	mid[3];
	double	result;

	if (vector_size(d) < 0.0001)
		return (0);
	vector_copy(mid, mlx->data.sp->cc);
	vector_minus(dot, mid, mid);
	result = inner_product(d, mid);
	a[0] = pow_2(vector_size(d));
	a[1] = 2 * result;
	a[2] = pow_2(vector_size(mid)) - pow_2(mlx->data.sp->r);
	exist = equation_d(a[0], a[1], a[2]);
	if (exist >= 0.0000001)
	{
		t = find_f(a[0], a[1], a[2], a[0]);
		if (t < 0.0001)
			return (0);
		return (1);
	}
	return (0);
}

int	check_hit_gray_sp(t_mlx *mlx, int i, int j)
{
	t_sphere	*save;
	double		light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		if (check_hit_gray_sp_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.sp = save;
			return (1);
		}
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
	return (0);
}

static int	check_hit_gray_pl_d(double *d, double *dot, t_mlx *mlx)
{
	double	t;

	if (inner_product(d, mlx->data.pl->nc) < 0.000001)
		return (0);
	t = (inner_product(mlx->data.pl->nc, mlx->data.pl->xc) \
		- inner_product(dot, mlx->data.pl->nc)) \
		/ inner_product(d, mlx->data.pl->nc);
	if (t <= 0.000001)
		return (0);
	return (1);
}

int	check_hit_gray_pl(t_mlx *mlx, int i, int j)
{
	t_plane	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.pl;
	while (mlx->data.pl != NULL)
	{
		if (check_hit_gray_pl_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.pl = save;
			return (1);
		}
		mlx->data.pl = mlx->data.pl->next;
	}
	mlx->data.pl = save;
	return (0);
}
