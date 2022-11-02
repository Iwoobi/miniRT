/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:06:10 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 22:06:20 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_cone_head(double *n, double h, double *c, double *result)
{
	vector_n(n, h, result);
	vector_plus(result, c, result);
}

void	check_hit_side_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	head[3];
	double	dot[3];
	double	a[3];
	double	val;
	int		i;

	mlx->t = -2;
	find_cone_head(n, mlx->data.cn->h, c, head);
	val = pow_2(mlx->data.cn->h) / (pow_2(mlx->data.cn->h) + pow_2(mlx->data.cn->r));
	a[0] = pow_2(inner_product(d, n)) - val * pow_2(vector_size(d));
	a[1] = 2 * (val * inner_product(head, d) - (inner_product(d, n) * inner_product(head, n)));
	a[2] = pow_2(inner_product(head, n)) - val * pow_2(vector_size(head));
	if (equation_d(a[0], a[1], a[2]) < 0)
		return ;
	i = 2;
	while (i > 0)
	{
		if (find_f(a[0], a[1], a[2], 2 * i - 3) >= 0)
		{
			vector_n(d, find_f(a[0], a[1], a[2], 2 * i - 3), dot);
			vector_minus(dot, c, dot);
			if (inner_product(dot, n) < mlx->data.cn->h)
			{
				if (inner_product(dot, n) > 0)
				{
					if (mlx->t > find_f(a[0], a[1], a[2], 2 * i - 3) || mlx->t < 0)
						mlx->t = find_f(a[0], a[1], a[2], 2 * i - 3);
					mlx->flag = 1;
				}
			}
		}
		i--;
	}
}

void	check_hit_bot_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	t;
	double	vec[3];

	if (inner_product(d, n) == 0)
		return ;
	t = inner_product(c, n) / inner_product(d, n);
	vector_n(d ,t, vec);
	if (t < EPSILON)
		return ;
	vector_minus(vec, c, vec);
	if (vector_size(vec) <= mlx->data.cn->r)
	{
		if (mlx->t > t || mlx->t < 0)
		{
			mlx->t = t;
			mlx->flag = 2;
		}
	}
}


int	check_hit_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	mlx->flag = 0;
	check_hit_side_cn_d(d, n, c, mlx);
	check_hit_bot_cn_d(d, n, c, mlx);
	if (mlx->flag != 0)
		uv_axis_cn(mlx, d);
	return (mlx->flag);
}

void	normal_vector_side_cn(t_mlx *mlx, int i, int j)
{
	double	head[3];
	double	cross_dot_n[3];
	double	cross_x[3];

	find_cone_head(mlx->data.cn->nc, mlx->data.cn->h, mlx->data.cn->cc, head);
	vector_n(mlx->ray[i][j].d, mlx->t, cross_dot_n);
	vector_minus(cross_dot_n, head, cross_dot_n);
	cross_product(cross_dot_n, mlx->data.cn->nc, cross_x);
	cross_product(cross_x, cross_dot_n, mlx->ray[i][j].n);
	normalize_vector(mlx->ray[i][j].n);
}

void	normal_vector_cn(t_mlx *mlx, int i, int j)
{
	if (mlx->flag == 2)
		vector_n(mlx->data.cn->nc, -1, mlx->ray[i][j].n);
	else if (mlx->flag == 1)
		normal_vector_side_cn(mlx, i, j);
}

void	check_hit_cn(t_mlx *mlx, double *d, int i, int j)
{
	t_cone	*save;

	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		normalize_vector(mlx->data.cn->nc);
		if (check_hit_cn_d(d, mlx->data.cn->nc, mlx->data.cn->cc, mlx) != 0)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, CN);
				normal_vector_cn(mlx, i, j);
				normal_vector_bump(mlx, i, j, CN);
			}
		}
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
}