/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cn_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:24:17 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 15:50:11 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	cone_utils_init(double *d, double *n, t_mlx *mlx, t_cone_utils *u)
{
	mlx->t = -2;
	u->i = 2;
	u->val = pow_2(mlx->data.cn->h) / (pow_2(mlx->data.cn->h) \
		+ pow_2(mlx->data.cn->r));
	u->a[0] = pow_2(inner_product(d, n)) - u->val * pow_2(vector_size(d));
	u->a[1] = 2 * (u->val * inner_product(u->head, d) - \
			(inner_product(d, n) * inner_product(u->head, n)));
	u->a[2] = pow_2(inner_product(u->head, n)) \
		- u->val * pow_2(vector_size(u->head));
}

static void	check_hit_side_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	t_cone_utils	u;

	find_cone_head(n, mlx->data.cn->h, c, u.head);
	cone_utils_init(d, n, mlx, &u);
	if (equation_d(u.a[0], u.a[1], u.a[2]) < 0)
		return ;
	while (u.i > 0)
	{
		if (find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3) >= 0)
		{
			vector_n(d, find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3), u.dot);
			vector_minus(u.dot, c, u.dot);
			if (inner_product(u.dot, n) < mlx->data.cn->h)
			{
				if (inner_product(u.dot, n) > 0)
				{
					if (mlx->t > find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3) \
						|| mlx->t < 0)
						mlx->t = find_f(u.a[0], u.a[1], u.a[2], 2 * u.i - 3);
					mlx->flag = 1;
				}
			}
		}
		u.i--;
	}
}

static void	check_hit_bot_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	t;
	double	vec[3];

	if (inner_product(d, n) == 0)
		return ;
	t = inner_product(c, n) / inner_product(d, n);
	vector_n(d, t, vec);
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
