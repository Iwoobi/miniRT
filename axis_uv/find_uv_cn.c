/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_uv_cn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:50:58 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:57:49 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	push_uv_cn_side(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];
	double	h;

	h = mlx->data.cn->h;
	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);
	mlx->data.cn->u[0] = (atan2(inner_product(vec, y), inner_product(vec, x))
			+ M_PI) / (2 * M_PI);
	mlx->data.cn->u[1] = fmod(inner_product(vec, mlx->data.cn->nc) / h, 1);
	mlx->data.cn->checker_u[0] = mlx->data.cn->r * 4
		* (atan2(inner_product(vec, x), inner_product(vec, y))
			+ M_PI) / (2 * M_PI);
	mlx->data.cn->checker_u[1] = round(fmod(inner_product(vec,
					mlx->data.cn->nc) * 3 / h, 1));
}

void	push_uv_cn_bot(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);
	mlx->data.cn->u[0] = (fmod(inner_product(x, vec), 1) / 2 + 1) / 2;
	mlx->data.cn->u[1] = (fmod(inner_product(y, vec), 1) / 2 + 1) / 2;
	mlx->data.cn->checker_u[0] = round(fmod(inner_product(x, vec)
				* 2 / mlx->data.cn->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cn->checker_u[0] -= 1;
	mlx->data.cn->checker_u[1] = round(fmod(inner_product(y, vec)
				* 2 / mlx->data.cn->r, 1));
	if (inner_product(y, vec) < 0)
		mlx->data.cn->checker_u[1] -= 1;
}

void	push_uv_cn(t_mlx *mlx, double *d, double *x, double *y)
{
	if (mlx->flag == 1)
		push_uv_cn_side(mlx, d, x, y);
	else if (mlx->flag == 2)
		push_uv_cn_bot(mlx, d, x, y);
}

void	uv_axis_cn(t_mlx *mlx, double *d)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(mlx->data.cn->nc, z, vec_y);
	cross_product(vec_y, mlx->data.cn->nc, vec_x);
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
	push_uv_cn(mlx, d, vec_x, vec_y);
}