/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:06:10 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 15:33:53 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	find_cone_head(double *n, double h, double *c, double *result)
{
	vector_n(n, h, result);
	vector_plus(result, c, result);
}

static void	normal_vector_side_cn(t_mlx *mlx, int i, int j)
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

static void	normal_vector_cn(t_mlx *mlx, int i, int j)
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
