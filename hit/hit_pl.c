/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:04:46 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 22:07:25 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	check_hit_pl_d(double *d, double *x, double *n, t_mlx *mlx)
{
	if (inner_product(d, n) == 0)
	{
		mlx->t = -2;
		return (0);
	}
	mlx->t = inner_product(x, n) / inner_product(d, n);
	if (mlx->t < 0)
	{
		mlx->t = -2;
		return (0);
	}
	if (mlx->data.pl->mode != NONE)
		uv_axis_pl(d, mlx);
	return (1);
}

void	normal_vector_pl(t_mlx *mlx, int i, int j)
{
	vector_copy(mlx->ray[i][j].n, mlx->data.pl->nc);
}

void	check_hit_pl(t_mlx *mlx, double *d, int i, int j)
{
	t_plane	*save;

	save = mlx->data.pl;
	while (mlx->data.pl != NULL)
	{
		normalize_vector(mlx->data.pl->nc);
		if (check_hit_pl_d(d, mlx->data.pl->xc, mlx->data.pl->nc, mlx) == 1)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0.000001)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, PL);
				normal_vector_pl(mlx, i, j);
				normal_vector_bump(mlx, i, j, PL);
			}
		}
		mlx->data.pl = mlx->data.pl->next;
	}
	mlx->data.pl = save;
}