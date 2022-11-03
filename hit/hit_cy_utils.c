/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:13:47 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 15:23:02 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	check_hit_top_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	l[3];
	double	vec[3];
	double	t;

	vector_n(n, mlx->data.cy->h, l);
	vector_plus(l, c, l);
	t = inner_product(n, l) / inner_product(d, n);
	vector_n(d, -t, vec);
	vector_plus(vec, l, vec);
	if (vector_size(vec) < mlx->data.cy->r)
	{
		if (mlx->t < 0.000001 || mlx->t > t)
		{
			mlx->t = t;
			mlx->flag = 3;
		}
	}
}

static void	check_hit_bot_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	t;
	double	vec[3];

	t = inner_product(n, c) / inner_product(d, n);
	vector_n(d, -t, vec);
	vector_plus(vec, c, vec);
	if (vector_size(vec) < mlx->data.cy->r)
	{
		if (mlx->t < 0.000001 || mlx->t > t)
		{
			mlx->t = t;
			mlx->flag = 2;
		}
	}
}

static int	check_hit_side_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	res1[3];
	double	res2[3];
	double	r;

	r = mlx->data.cy->r;
	cross_product(c, n, res1);
	cross_product(d, n, res2);
	if (equation_d(pow_2(vector_size(res2)), -2 * inner_product(res1, res2), \
					pow_2(vector_size(res1)) - r * r) >= 0)
	{
		mlx->t = find_f(pow_2(vector_size(res2)), -2 \
			* inner_product(res1, res2), pow_2(vector_size(res1)) - r * r, 1);
		if (inner_product(d, n) * mlx->t - inner_product(c, n) \
			<= mlx->data.cy->h)
		{
			if (inner_product(d, n) * mlx->t - inner_product(c, n) >= 0.000001)
			{
				mlx->flag = 1;
				return (1);
			}
		}
		mlx->t = -2;
	}
	return (0);
}

int	check_hit_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	mlx->flag = 0;
	check_hit_side_cy_d(d, n, c, mlx);
	check_hit_bot_cy_d(d, n, c, mlx);
	check_hit_top_cy_d(d, n, c, mlx);
	return (mlx->flag);
}
