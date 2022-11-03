/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_uv_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:41:09 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 18:33:38 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	push_uv_pl(t_mlx *mlx, double *d, double *x, double *y)
{
	double	dot[3];

	vector_n(d, mlx->t, dot);
	vector_minus(dot, mlx->data.pl->xc, dot);
	mlx->data.pl->u[0] = (fmod(inner_product(x, dot), 1) + 1) / 2;
	mlx->data.pl->u[1] = (fmod(inner_product(y, dot), 1) + 1) / 2;
	mlx->data.pl->checker_u[0] = round(fmod(inner_product(x, dot), 1));
	if (inner_product(x, dot) < 0)
		mlx->data.pl->checker_u[0] -= 1;
	mlx->data.pl->checker_u[1] = round(fmod(inner_product(y, dot), 1));
	if (inner_product(y, dot) < 0)
		mlx->data.pl->checker_u[1] -= 1;
}

void	uv_axis_pl(double *d, t_mlx *mlx)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(mlx->data.pl->nc, z, vec_y);
	cross_product(vec_y, mlx->data.pl->nc, vec_x);
	if (vector_size(vec_y) == 0)
	{
		axis_y(vec_y);
		axis_x(vec_x);
	}
	else
	{
		normalize_vector(vec_y);
		normalize_vector(vec_x);
	}
	push_uv_pl(mlx, d, vec_x, vec_y);
}
