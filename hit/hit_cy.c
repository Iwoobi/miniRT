/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:09:13 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 15:15:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	normal_vector_top_cy(t_mlx *mlx, int i, int j)
{
	vector_copy(mlx->ray[i][j].n, mlx->data.cy->nc);
}

static void	normal_vector_bot_cy(t_mlx *mlx, int i, int j)
{
	double	vec[3];

	vector_n(mlx->data.cy->nc, -1, vec);
	vector_copy(mlx->ray[i][j].n, vec);
}

static void	normal_vector_cy(t_mlx *mlx, double	*d, int i, int j)
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
