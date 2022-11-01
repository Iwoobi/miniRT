/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:56:21 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 20:52:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	init_number(t_mlx *mlx)
{
	mlx->size[0] = WINDOW_WIDTH;
	mlx->size[1] = WINDOW_HEIGHT;
	mlx->cam_num = 0;
	mlx->data.num.count_l = 0;
	mlx->data.num.count_al = 0;
	mlx->data.num.count_cam = 0;
	mlx->data.num.count_sp = 0;
	mlx->data.num.count_pl = 0;
	mlx->data.num.count_cy = 0;
	mlx->data.num.count_cn = 0;
}

static void	init_ray(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->ray = (t_ray **)malloc(sizeof(t_ray *) * WINDOW_WIDTH);
	if (mlx->ray == NULL)
		print_error("malloc error.");
	while (i < WINDOW_WIDTH)
	{
		mlx->ray[i] = malloc(sizeof(t_ray) * WINDOW_HEIGHT);
		if (mlx->ray[i] == NULL)
			print_error("malloc error.");
		i++;
	}
}

static void	init_object(t_mlx *mlx)
{
	mlx->data.cn = (t_cone *)malloc(sizeof(t_cone) * 1);
	mlx->data.al = (t_alight *)malloc(sizeof(t_alight) * 1);
	mlx->data.cam = (t_cam *)malloc(sizeof(t_cam) * 1);
	mlx->data.l = (t_light *)malloc(sizeof(t_light) * 1);
	mlx->data.pl = (t_plane *)malloc(sizeof(t_plane) * 1);
	mlx->data.cy = (t_cylinder *)malloc(sizeof(t_cylinder) * 1);
	mlx->data.sp = (t_sphere *)malloc(sizeof(t_sphere) * 1);
	if (mlx->data.al == NULL || mlx->data.cam == NULL || mlx->data.l == NULL)
		print_error("malloc error.");
	if (mlx->data.pl == NULL || mlx->data.cy == NULL || mlx->data.sp == NULL)
		print_error("malloc error.");
	if (mlx->data.cn == NULL)
		print_error("malloc error.");
	mlx->data.al->next = NULL;
	mlx->data.cn->next = NULL;
	mlx->data.l->next = NULL;
	mlx->data.cam->next = NULL;
	mlx->data.pl->next = NULL;
	mlx->data.cy->next = NULL;
	mlx->data.sp->next = NULL;
}

void	init_mlx_data(t_mlx *mlx)
{
	init_number(mlx);
	init_ray(mlx);
	init_object(mlx);
}
