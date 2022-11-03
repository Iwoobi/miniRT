/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:04:02 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 18:17:55 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	check_hit_gray_cy_top_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	c[3];
	double	t;

	vector_n(mlx->data.cy->nc, mlx->data.cy->h, c);
	vector_plus(c, mlx->data.cy->cc, c);
	vector_minus(c, dot, vec);
	if (inner_product(d, mlx->data.cy->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cy->nc) \
		/ inner_product(d, mlx->data.cy->nc);
	if (t < 0.000001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, c, vec);
	if (vector_size(vec) > mlx->data.cy->r)
		return (0);
	return (1);
}

static int	check_hit_gray_cy_bot_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	t;

	vector_minus(mlx->data.cy->cc, dot, vec);
	if (inner_product(d, mlx->data.cy->nc) <= 0)
		return (0);
	t = inner_product(vec, mlx->data.cy->nc) \
		/ inner_product(d, mlx->data.cy->nc);
	if (t < 0.001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	if (vector_size(vec) > mlx->data.cy->r)
		return (0);
	return (1);
}

static int	check_hit_gray_cy_side_d(double *d, double *dot, t_mlx *mlx)
{
	double	cross_d_n[3];
	double	cross_dot_c_n[3];
	double	vec[3];
	double	t;

	vector_minus(dot, mlx->data.cy->cc, vec);
	cross_product(d, mlx->data.cy->nc, cross_d_n);
	cross_product(vec, mlx->data.cy->nc, cross_dot_c_n);
	t = mlx->data.cy->r;
	if (equation_d(pow_2(vector_size(cross_d_n)), \
		2 * inner_product(cross_dot_c_n, cross_d_n), \
		pow_2(vector_size(cross_dot_c_n)) - pow_2(t)) < 0)
		return (0);
	t = find_f(pow_2(vector_size(cross_d_n)), 2 * inner_product(cross_dot_c_n, \
		cross_d_n), pow_2(vector_size(cross_dot_c_n)) - pow_2(t), 1);
	if (t < 0.00000001)
		return (0);
	if (inner_product(d, mlx->data.cy->nc) * t + inner_product(vec, \
		mlx->data.cy->nc) < mlx->data.cy->h)
	{
		if (inner_product(d, mlx->data.cy->nc) * t \
			+ inner_product(vec, mlx->data.cy->nc) > 0)
			return (1);
	}
	return (0);
}

static int	check_hit_gray_cy_d(double *d, double *dot, t_mlx *mlx)
{
	if (check_hit_gray_cy_top_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cy_bot_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cy_side_d(d, dot, mlx) == 1)
		return (1);
	return (0);
}

int	check_hit_gray_cy(t_mlx *mlx, int i, int j)
{
	t_cylinder	*save;
	double		light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.cy;
	while (mlx->data.cy != NULL)
	{
		if (check_hit_gray_cy_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.cy = save;
			return (1);
		}
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
	return (0);
}
