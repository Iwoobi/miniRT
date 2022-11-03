/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:00:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 15:11:29 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	check_hit_sp_d(double *d, double *c, t_mlx *mlx)
{
	double	a;
	double	r;

	r = mlx->data.sp->r;
	a = equation_d(pow_2(vector_size(d)), -2 * inner_product(d, c), \
					pow_2(vector_size(c)) - r * r);
	if (a >= 0.000001)
	{
		mlx->t = find_f(pow_2(vector_size(d)), -2 * inner_product(d, c), \
						pow_2(vector_size(c)) - r * r, 1);
		if (mlx->t < 0.0001)
		{
			mlx->t = -2;
			return (0);
		}
		if (mlx->data.sp->mode != NONE)
			uv_axis_sp(d, mlx);
		return (1);
	}
	mlx->t = -2;
	return (0);
}

void	normal_vector_sp(t_mlx *mlx, double	*d, int i, int j)
{
	double	x[3];

	x[0] = d[0] * mlx->t - mlx->data.sp->cc[0];
	x[1] = d[1] * mlx->t - mlx->data.sp->cc[1];
	x[2] = d[2] * mlx->t - mlx->data.sp->cc[2];
	normalize_vector(x);
	mlx->ray[i][j].n[0] = x[0];
	mlx->ray[i][j].n[1] = x[1];
	mlx->ray[i][j].n[2] = x[2];
}

void	check_hit_sp(t_mlx *mlx, double *d, int i, int j)
{
	t_sphere	*save;

	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		if (check_hit_sp_d(d, mlx->data.sp->cc, mlx) == 1)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0.000001)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, SP);
				normal_vector_sp(mlx, d, i, j);
				normal_vector_bump(mlx, i, j, SP);
			}
		}
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
}
