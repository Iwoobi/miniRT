/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_cn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:08:51 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 16:22:34 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	check_hit_gray_cn_bot_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	t;

	vector_minus(mlx->data.cn->cc, dot, vec);
	if (inner_product(d, mlx->data.cn->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cn->nc) \
		/ inner_product(d, mlx->data.cn->nc);
	if (t < 0.0001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);
	if (vector_size(vec) > mlx->data.cn->r)
		return (0);
	return (1);
}

static void	cone_utils_init(double *d, t_mlx *mlx, t_cone_utils *u)
{
	u->i = 2;
	u->val = (pow_2(mlx->data.cn->h) \
		/ (pow_2(mlx->data.cn->h) + pow_2(mlx->data.cn->r)));
	u->a[0] = pow_2(inner_product(d, mlx->data.cn->nc)) \
		- u->val * pow_2(vector_size(d));
	u->a[1] = 2 * (u->val * inner_product(u->head, d) \
		- (inner_product(d, mlx->data.cn->nc) \
		* inner_product(u->head, mlx->data.cn->nc)));
	u->a[2] = pow_2(inner_product(u->head, mlx->data.cn->nc)) \
		- u->val * pow_2(vector_size(u->head));
}

static int	check_hit_gray_cn_side_d(double *d, double *dot, t_mlx *mlx)
{
	t_cone_utils	u;

	find_cone_head(mlx->data.cn->nc, mlx->data.cn->h, \
		mlx->data.cn->cc, u.head);
	vector_minus(u.head, dot, u.head);
	cone_utils_init(d, mlx, &u);
	if (equation_d(u.a[0], u.a[1], u.a[2]) < 0)
		return (0);
	while (u.i > 0)
	{
		if (find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3) > 0.001)
		{
			vector_n(d, find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3), u.dot);
			vector_plus(u.dot, dot, u.dot);
			vector_minus(u.dot, mlx->data.cn->cc, u.dot);
			if (inner_product(u.dot, mlx->data.cn->nc) < mlx->data.cn->h)
			{
				if (inner_product(u.dot, mlx->data.cn->nc) > 0)
					return (1);
			}
		}
		u.i--;
	}
	return (0);
}

static int	check_hit_gray_cn_d(double *d, double *dot, t_mlx *mlx)
{
	if (check_hit_gray_cn_bot_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cn_side_d(d, dot, mlx) == 1)
		return (1);
	return (0);
}

int	check_hit_gray_cn(t_mlx *mlx, int i, int j)
{
	t_cone	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		if (check_hit_gray_cn_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.cn = save;
			return (1);
		}
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
	return (0);
}
