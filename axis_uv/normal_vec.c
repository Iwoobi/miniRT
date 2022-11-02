/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:20:46 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:30:01 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	push_normal_bump(double rot[3][3], double *x, double *y, double *z)
{
	rot[0][0] = x[0];
	rot[0][1] = y[0];
	rot[0][2] = z[0];
	rot[1][0] = x[1];
	rot[1][1] = y[1];
	rot[1][2] = z[1];
	rot[2][0] = x[2];
	rot[2][1] = y[2];
	rot[2][2] = z[2];
}

void	bump_rot_data_init(double rot[3][3], double *n)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(n, z, vec_y);
	cross_product(vec_y, n, vec_x);
	if (vector_size(vec_y) == 0)
	{
		axis_y(vec_y);
		axis_x(vec_x);
		if (inner_product(n, z) < 0)
		{
			vector_n(vec_y, -1, vec_y);
			vector_n(vec_x, -1, vec_x);
		}
	}
	else
	{
		normalize_vector(vec_y);
		normalize_vector(vec_x);
	}
	push_normal_bump(rot, vec_x, vec_y, n);
}

void	updata_normal_vector(double *u, t_img n, double rot[3][3], double *res)
{
	double	vec[3];
	int		i;
	int		j;

	i = u[0] * n.w;
	j = u[1] * n.h;
	hex_to_rgb_double(n.data[i + n.w * j], &(vec[0]));
	vec[1] = vec[1] / 255;
	vec[0] = vec[0] / 255;
	vec[2] = vec[2] / 255;
	vector_n(vec, 2, vec);
	vec[0] -= 1;
	vec[1] -= 1;
	vec[2] -= 1;
	res[0] = inner_product(rot[0], vec);
	res[1] = inner_product(rot[1], vec);
	res[2] = inner_product(rot[2], vec);
}

void	normal_vector_bump2(t_mlx *mlx, int i, int j, t_obj obj)
{
	double	rot[3][3];

	bump_rot_data_init(rot, mlx->ray[i][j].n);
	if (obj == CN)
	{
		if (mlx->data.cn->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.cn->u,
			mlx->data.cn->xpm.normal, rot, mlx->ray[i][j].n);
	}
	else if (obj == PL)
	{
		if (mlx->data.pl->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.pl->u,
			mlx->data.pl->xpm.normal, rot, mlx->ray[i][j].n);
	}
}

void	normal_vector_bump(t_mlx *mlx, int i, int j, t_obj obj)
{
	double	rot[3][3];

	bump_rot_data_init(rot, mlx->ray[i][j].n);
	if (obj == SP)
	{
		if (mlx->data.sp->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.sp->u,
			mlx->data.sp->xpm.normal, rot, mlx->ray[i][j].n);
	}
	else if (obj == CY)
	{
		if (mlx->data.cy->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.cy->u,
			mlx->data.cy->xpm.normal, rot, mlx->ray[i][j].n);
	}
	else
		normal_vector_bump2(mlx, i, j, obj);
}
