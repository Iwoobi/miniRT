/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_uv_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:43:15 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:58:02 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	push_uv_cy_side(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	mlx->data.cy->u[0] = (atan2(inner_product(vec, y),
				inner_product(vec, x)) + M_PI) / (2 * M_PI);
	mlx->data.cy->u[1] = fmod(inner_product(vec,
				mlx->data.cy->nc) / mlx->data.cy->h, 1);
	mlx->data.cy->checker_u[0] = mlx->data.cy->r * 17 * M_PI
		* (atan2(inner_product(vec, x), inner_product(vec, y)) + M_PI)
		/ (2 * M_PI) / mlx->data.cy->h;
	mlx->data.cy->checker_u[1]
		= round(fmod(inner_product(vec, mlx->data.cy->nc), 1));
}

void	push_uv_cy_top(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];
	double	head[3];

	vector_n(mlx->data.cy->nc, mlx->data.cy->h, head);
	vector_plus(mlx->data.cy->cc, head, head);
	vector_n(d, mlx->t, vec);
	vector_minus(vec, head, vec);
	mlx->data.cy->u[0] = (fmod(inner_product(x, vec), 1) + 1) / 2;
	mlx->data.cy->u[1] = (fmod(inner_product(y, vec), 1) + 1) / 2;
	mlx->data.cy->checker_u[0] = round(fmod(inner_product(x, vec)
				* 2 / mlx->data.cy->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cy->checker_u[0] -= 1;
	mlx->data.cy->checker_u[1] = round(fmod(inner_product(y, vec)
				* 2 / mlx->data.cy->r, 1));
	if (inner_product(y, vec) < 0)
		mlx->data.cy->checker_u[1] -= 1;
}

void	push_uv_cy_bot(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	mlx->data.cy->u[0] = (fmod(inner_product(x, vec), 1) + 1) / 2;
	mlx->data.cy->u[1] = (fmod(inner_product(y, vec), 1) + 1) / 2;
	mlx->data.cy->checker_u[0] = round(fmod(inner_product(x, vec)
				* 2 / mlx->data.cy->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cy->checker_u[0] -= 1;
	mlx->data.cy->checker_u[1] = round(fmod(inner_product(y, vec)
				* 2 / mlx->data.cy->r, 1));
	if (inner_product(y, vec) < 0)
		mlx->data.cy->checker_u[1] -= 1;
}

void	push_uv_cy(t_mlx *mlx, double *d, double *x, double *y)
{
	if (mlx->flag == 1)
		push_uv_cy_side(mlx, d, x, y);
	else if (mlx->flag == 2)
		push_uv_cy_bot(mlx, d, x, y);
	else if (mlx->flag == 3)
		push_uv_cy_top(mlx, d, x, y);
}

void	uv_axis_cy(t_mlx *mlx, double *d)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(mlx->data.cy->nc, z, vec_y);
	cross_product(vec_y, mlx->data.cy->nc, vec_x);
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
	push_uv_cy(mlx, d, vec_x, vec_y);
}
