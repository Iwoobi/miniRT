/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:43:50 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 16:24:06 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_point(t_mlx *mlx, int i, int j)
{
	double	d[3];

	int k = 2;

	d[0] = ((k * floor(i/k) / 1599)) * 2 * tan(deg_to_rad(mlx->data.cam->fov) / 2) - tan(deg_to_rad(mlx->data.cam->fov) / 2) + (k - 1)*(1/2) * 2 * tan(deg_to_rad(mlx->data.cam->fov) / 2) / 1599 ;
	d[1] = 9 * (k * (2 * (floor(j/k) / 899)) * tan(deg_to_rad(mlx->data.cam->fov) / 2) - tan(deg_to_rad(mlx->data.cam->fov) / 2) + (k - 1)*(1/2) * 2 * tan(deg_to_rad(mlx->data.cam->fov) / 2) / 899)/16;
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

int	loop_main(t_mlx *mlx)
{
	t_mdata	rot;

	copy_rot_data(mlx);
	rot = data_cam_num_init(*mlx);
	exec_rot_data(mlx, rot);
	canvas_match(mlx);
	phong_init(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		exit(0);
	init_mlx_data(&mlx);
	ft_mlx_init(&mlx);
	check_input(argv[1], &mlx);
	mlx_hook(mlx.win, PRESS, 0, &press_key, &mlx);
	mlx_hook(mlx.win, CLOSED, 0, &ft_close, &mlx);
	mlx_loop_hook(mlx.mlx, &loop_main, &mlx);
	mlx_loop(mlx.mlx);
}