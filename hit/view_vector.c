/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:42:33 by youhan            #+#    #+#             */
/*   Updated: 2022/11/07 19:36:29 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	hit_point(t_mlx *mlx, int i, int j)
{
	double	d[3];

	d[0] = ((PIXEL * floor(i / PIXEL) / 1599)) * 2 \
		* tan(deg_to_rad(mlx->data.cam->fov) / 2) \
		- tan(deg_to_rad(mlx->data.cam->fov) / 2) + (PIXEL - 1) * (1 / 2) * 2 \
		* tan(deg_to_rad(mlx->data.cam->fov) / 2) / 1599;
	d[1] = 9 * (PIXEL * (2 * (floor(j / PIXEL) / 899)) \
		* tan(deg_to_rad(mlx->data.cam->fov) / 2) \
		- tan(deg_to_rad(mlx->data.cam->fov) / 2) + (PIXEL - 1) * (1 / 2) * 2 \
		* tan(deg_to_rad(mlx->data.cam->fov) / 2) / 899) / 16;
	d[2] = 1;
	normalize_vector(d);
	mlx->ray[i][j].d[0] = d[0];
	mlx->ray[i][j].d[1] = d[1];
	mlx->ray[i][j].d[2] = d[2];
	check_hit_sp(mlx, d, i, j);
	check_hit_cy(mlx, d, i, j);
	check_hit_pl(mlx, d, i, j);
	check_hit_cn(mlx, d, i, j);
}

void	canvas_match(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			mlx->ray[i][j].deep = -3;
			mlx->ray[i][j].sum_rgb[0] = 0;
			mlx->ray[i][j].sum_rgb[1] = 0;
			mlx->ray[i][j].sum_rgb[2] = 0;
			hit_point(mlx, i, j);
			j++;
		}
		i++;
	}
}
