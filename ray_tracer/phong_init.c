/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:52:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/07 19:27:13 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	sum_color(t_mlx *mlx, int i, int j, unsigned int phong[3][3])
{
	mlx->ray[i][j].sum_rgb[0] += phong[1][0] + phong[2][0];
	mlx->ray[i][j].sum_rgb[1] += phong[1][1] + phong[2][1];
	mlx->ray[i][j].sum_rgb[2] += phong[1][2] + phong[2][2];
	if (mlx->ray[i][j].sum_rgb[0] > 255)
		mlx->ray[i][j].sum_rgb[0] = 255;
	if (mlx->ray[i][j].sum_rgb[1] > 255)
		mlx->ray[i][j].sum_rgb[1] = 255;
	if (mlx->ray[i][j].sum_rgb[2] > 255)
		mlx->ray[i][j].sum_rgb[2] = 255;
}

static void	gray_exist(t_mlx *mlx, int i, int j, unsigned int phong[3][3])
{
	if (check_hit_gray_sp(mlx, i, j) == 1)
		reset_phong_light(phong);
	else if (check_hit_gray_pl(mlx, i, j) == 1)
		reset_phong_light(phong);
	else if (check_hit_gray_cy(mlx, i, j) == 1)
		reset_phong_light(phong);
	else if (check_hit_gray_cn(mlx, i, j) == 1)
		reset_phong_light(phong);
}

static void	find_ray_dot(t_mlx *mlx, int i, int j)
{	
	mlx->ray[i][j].dot[0] = mlx->ray[i][j].deep * mlx->ray[i][j].d[0];
	mlx->ray[i][j].dot[1] = mlx->ray[i][j].deep * mlx->ray[i][j].d[1];
	mlx->ray[i][j].dot[2] = mlx->ray[i][j].deep * mlx->ray[i][j].d[2];
}

static void	phong_point(t_mlx *mlx, int i, int j)
{
	unsigned int	phong[3][3];
	t_light			*save;
	int				k;

	save = mlx->data.l;
	phong_reset(phong);
	if (mlx->data.num.count_al != 0)
		ambient_light(mlx, i, j, phong[0]);
	mlx->ray[i][j].sum_rgb[0] += phong[0][0];
	mlx->ray[i][j].sum_rgb[1] += phong[0][1];
	mlx->ray[i][j].sum_rgb[2] += phong[0][2];
	k = 0;
	while (mlx->data.num.count_l > k)
	{
		diffuse_light(mlx, i, j, phong[1]);
		specular_light(mlx, i, j, phong[2]);
		gray_exist(mlx, i, j, phong);
		sum_color(mlx, i, j, phong);
		mlx->data.l = mlx->data.l->next;
		k++;
	}
	mlx->img.data[WINDOW_WIDTH * j + i] = apply_color(mlx->ray[i][j].sum_rgb);
	mlx->data.l = save;
}

void	phong_init(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			if (mlx->ray[i][j].deep > 0)
			{
				find_ray_dot(mlx, i, j);
				phong_point(mlx, i, j);
			}
			j++;
		}
		i++;
	}
}
