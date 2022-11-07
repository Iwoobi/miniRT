/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:16:09 by youhan            #+#    #+#             */
/*   Updated: 2022/11/07 18:31:40 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	rot_matrix(double *x, double *y, double *z, double *result)
{
	result[0] = x[0] / vector_size(x);
	result[1] = x[1] / vector_size(x);
	result[2] = x[2] / vector_size(x);
	result[3] = y[0] / vector_size(y);
	result[4] = y[1] / vector_size(y);
	result[5] = y[2] / vector_size(y);
	result[6] = z[0] / vector_size(z);
	result[7] = z[1] / vector_size(z);
	result[8] = z[2] / vector_size(z);
}

void	rot_data_push(t_cam cam, t_mdata *data)
{
	double	x[3];
	double	y[3];
	double	z[3];

	z[0] = 0;
	z[1] = 0;
	z[2] = 1;
	cross_product(cam.n, z, x);
	cross_product(cam.n, x, y);
	rot_matrix(x, y, cam.n, data->rot);
}

void	rot_non_data_push(t_cam cam, t_mdata *data)
{
	data->rot[0] = cam.n[2] / sqrt(cam.n[2] * cam.n[2]);
	data->rot[1] = 0;
	data->rot[2] = 0;
	data->rot[3] = 0;
	data->rot[4] = cam.n[2] / sqrt(cam.n[2] * cam.n[2]);
	data->rot[5] = 0;
	data->rot[6] = 0;
	data->rot[7] = 0;
	data->rot[8] = cam.n[2] / sqrt(cam.n[2] * cam.n[2]);
}

t_mdata	rot_data_init(t_cam	cam)
{
	t_mdata	data;

	data.m[0] = cam.x[0];
	data.m[1] = cam.x[1];
	data.m[2] = cam.x[2];
	if (rot_data_check(cam) == -1)
		rot_non_data_push(cam, &data);
	else
		rot_data_push(cam, &data);
	return (data);
}

t_mdata	data_cam_num_init(t_mlx mlx)
{
	int		i;

	i = 0;
	while (i < mlx.cam_num)
	{
		mlx.data.cam = mlx.data.cam->next;
		i++;
	}
	return (rot_data_init(*(mlx.data.cam)));
}
