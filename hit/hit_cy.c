/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:09:13 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 22:13:27 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	normal_vector_top_cy(t_mlx *mlx, int i, int j)
{
	vector_copy(mlx->ray[i][j].n, mlx->data.cy->nc);
}

void	normal_vector_bot_cy(t_mlx *mlx, int i, int j)
{
	double	vec[3];

	vector_n(mlx->data.cy->nc, -1, vec);
	vector_copy(mlx->ray[i][j].n, vec);
}

void	normal_vector_cy(t_mlx *mlx, double	*d, int i, int j)
{
	double	x[3];
	double	c[3];
	
	if (mlx->flag == 3)
		normal_vector_top_cy(mlx, i, j);
	else if (mlx->flag == 2)
		normal_vector_bot_cy(mlx, i, j);
	else if (mlx->flag == 1)
	{
		vector_n(d, mlx->ray[i][j].deep, x);
		vector_n(mlx->data.cy->cc, -1, c);
		vector_plus(x, c, x);
		normalize_vector(mlx->data.cy->nc);
		vector_n(mlx->data.cy->nc, -inner_product(x, mlx->data.cy->nc), c);
		vector_plus(x, c, x);
		normalize_vector(x);
		vector_copy(mlx->ray[i][j].n, x);
	}
}

void	check_hit_top_cy_d(double *d, double *n, double *c, t_mlx *mlx)
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

void	check_hit_bot_cy_d(double *d, double *n, double *c, t_mlx *mlx)
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

int	check_hit_side_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	a;
	double	result1[3];
	double	result2[3];
	double	r;

	r = mlx->data.cy->r;
	cross_product(c, n, result1);
	cross_product(d, n, result2);
	a = equation_d(pow_2(vector_size(result2)), -2 * inner_product(result1, result2), pow_2(vector_size(result1)) - r * r);
	if (a >= 0)
	{
		mlx->t = find_f(pow_2(vector_size(result2)), -2 * inner_product(result1, result2), pow_2(vector_size(result1)) - r * r, 1);
		if (inner_product(d, n) * mlx->t - inner_product(c, n) <= mlx->data.cy->h)
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

void	check_hit_cy(t_mlx *mlx, double *d, int i, int j)
{
	t_cylinder	*save;

	save = mlx->data.cy;
	while (mlx->data.cy != NULL)
	{
		normalize_vector(mlx->data.cy->nc);
		if (check_hit_cy_d(d, mlx->data.cy->nc, mlx->data.cy->cc, mlx) != 0)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0)
			{
				mlx->ray[i][j].deep = mlx->t;
				if (mlx->data.cy->mode != NONE)
					uv_axis_cy(mlx, d);
				color_select(mlx, mlx->ray[i][j].rgb, CY);
				normal_vector_cy(mlx, d, i, j);
				normal_vector_bump(mlx, i, j, CY);
			}
		}
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
}
