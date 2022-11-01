/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:43:50 by youhan            #+#    #+#             */
/*   Updated: 2022/11/01 20:59:44 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	 rot_matrix(double *x, double *y, double *z, double *result)
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

int	rot_data_check(t_cam cam)
{
	if (cam.n[0] == 0)
	{
		if (cam.n[1] == 0)
		{
			if (cam.n[2] != 0)
				return (-1);
			print_error("invalid camera rotate.");
		}
	}
	return (0);
}

void	rot_non_data_push(t_cam cam, t_mdata *data)
{
	data->rot[0] = cam.n[2] / sqrt(cam.n[2] * cam.n[2]);;
	data->rot[1] = 0;
	data->rot[2] = 0;
	data->rot[3] = 0;
	data->rot[4] = cam.n[2] / sqrt(cam.n[2] * cam.n[2]);;
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

void	trans_rot_data(double x[3], t_mdata mdata)
{
	double	save[3];

	save[0] = x[0];
	save[1] = x[1];
	save[2] = x[2];
	x[0] = mdata.rot[0] * save[0] + mdata.rot[1] * save[1] + mdata.rot[2] * save[2];
	x[1] = mdata.rot[3] * save[0] + mdata.rot[4] * save[1] + mdata.rot[5] * save[2];
	x[2] = mdata.rot[6] * save[0] + mdata.rot[7] * save[1] + mdata.rot[8] * save[2];
}

void	updata_rot_l(t_data *data, t_mdata mdata)
{
	t_light	*save;

	save = data->l;
	while (data->l != NULL)
	{
		data->l->xc[0] -= mdata.m[0];
		data->l->xc[1] -= mdata.m[1];
		data->l->xc[2] -= mdata.m[2];
		trans_rot_data(data->l->xc, mdata); 
		data->l = data->l->next;
	}
	data->l = save;
}

void	updata_rot_sp(t_data *data, t_mdata mdata)
{
	t_sphere	*save;

	save = data->sp;
	while (data->sp != NULL)
	{
		data->sp->cc[0] -= mdata.m[0];
		data->sp->cc[1] -= mdata.m[1];
		data->sp->cc[2] -= mdata.m[2];
		trans_rot_data(data->sp->cc, mdata); 
		data->sp = data->sp->next;
	}
	data->sp = save;
}

void	updata_rot_pl(t_data *data, t_mdata mdata)
{
	t_plane	*save;

	save = data->pl;
	while (data->pl != NULL)
	{
		data->pl->xc[0] -= mdata.m[0];
		data->pl->xc[1] -= mdata.m[1];
		data->pl->xc[2] -= mdata.m[2];
		trans_rot_data(data->pl->xc, mdata);
		trans_rot_data(data->pl->nc, mdata); 
		data->pl = data->pl->next;
	}
	data->pl = save;
}

void	updata_rot_cy(t_data *data, t_mdata mdata)
{
	t_cylinder	*save;

	save = data->cy;
	while (data->cy != NULL)
	{
		data->cy->cc[0] -= mdata.m[0];
		data->cy->cc[1] -= mdata.m[1];
		data->cy->cc[2] -= mdata.m[2];
		trans_rot_data(data->cy->cc, mdata);
		trans_rot_data(data->cy->nc, mdata); 
		data->cy = data->cy->next;
	}
	data->cy = save;
}

void	updata_rot_cn(t_data *data, t_mdata mdata)
{
	t_cone	*save;

	save = data->cn;
	while (data->cn != NULL)
	{
		data->cn->cc[0] -= mdata.m[0];
		data->cn->cc[1] -= mdata.m[1];
		data->cn->cc[2] -= mdata.m[2];
		trans_rot_data(data->cn->cc, mdata);
		trans_rot_data(data->cn->nc, mdata);
		data->cn = data->cn->next;
	}
	data->cn = save;
}


void	updata_rot(t_mlx *mlx, t_mdata mdata)
{
	updata_rot_l(&(mlx->data), mdata);
	updata_rot_sp(&(mlx->data), mdata);
	updata_rot_pl(&(mlx->data), mdata);
	updata_rot_cy(&(mlx->data), mdata);
	updata_rot_cn(&(mlx->data), mdata);
}



void	copy_rot_l(t_mlx *mlx)
{
	t_light	*save;

	save = mlx->data.l;
	while (mlx->data.l != NULL)
	{
		mlx->data.l->xc[0] = mlx->data.l->x[0];
		mlx->data.l->xc[1] = mlx->data.l->x[1];
		mlx->data.l->xc[2] = mlx->data.l->x[2];
		mlx->data.l = mlx->data.l->next;
	}
	mlx->data.l = save;
}

void	copy_rot_sp(t_mlx *mlx)
{
	t_sphere	*save;

	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		mlx->data.sp->cc[0] = mlx->data.sp->c[0];
		mlx->data.sp->cc[1] = mlx->data.sp->c[1];
		mlx->data.sp->cc[2] = mlx->data.sp->c[2];
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
}

void	copy_rot_pl(t_mlx *mlx)
{
	t_plane	*save;

	save = mlx->data.pl;
	while (mlx->data.pl != NULL)
	{
		mlx->data.pl->xc[0] = mlx->data.pl->x[0];
		mlx->data.pl->xc[1] = mlx->data.pl->x[1];
		mlx->data.pl->xc[2] = mlx->data.pl->x[2];
		mlx->data.pl->nc[0] = mlx->data.pl->n[0];
		mlx->data.pl->nc[1] = mlx->data.pl->n[1];
		mlx->data.pl->nc[2] = mlx->data.pl->n[2];
		mlx->data.pl = mlx->data.pl->next;
	}
	mlx->data.pl = save;
}

void	copy_rot_cy(t_mlx *mlx)
{
	t_cylinder	*save;

	save = mlx->data.cy;
	while (mlx->data.cy != NULL)
	{
		mlx->data.cy->cc[0] = mlx->data.cy->c[0];
		mlx->data.cy->cc[1] = mlx->data.cy->c[1];
		mlx->data.cy->cc[2] = mlx->data.cy->c[2];
		mlx->data.cy->nc[0] = mlx->data.cy->n[0];
		mlx->data.cy->nc[1] = mlx->data.cy->n[1];
		mlx->data.cy->nc[2] = mlx->data.cy->n[2];
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
}

void	copy_rot_cn(t_mlx *mlx)
{
	t_cone	*save;

	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		mlx->data.cn->cc[0] = mlx->data.cn->c[0];
		mlx->data.cn->cc[1] = mlx->data.cn->c[1];
		mlx->data.cn->cc[2] = mlx->data.cn->c[2];
		mlx->data.cn->nc[0] = mlx->data.cn->n[0];
		mlx->data.cn->nc[1] = mlx->data.cn->n[1];
		mlx->data.cn->nc[2] = mlx->data.cn->n[2];
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
}

void	copy_rot_data(t_mlx *mlx)
{
	copy_rot_l(mlx);
	copy_rot_sp(mlx);
	copy_rot_pl(mlx);
	copy_rot_cy(mlx);
	copy_rot_cn(mlx);
}

void	axis_x(double *result)
{
	result[0] = 1;
	result[1] = 0;
	result[2] = 0;
}

void	axis_y(double *result)
{
	result[0] = 0;
	result[1] = 1;
	result[2] = 0;
}

void	axis_z(double *result)
{
	result[0] = 0;
	result[1] = 0;
	result[2] = 1;
}

void	uv_axis_sp(double *d, t_mlx *mlx)
{
	double	x[3];
	double	size;
	
	x[0] = mlx->t * d[0] - mlx->data.sp->cc[0];
	x[1] = mlx->t * d[1] - mlx->data.sp->cc[1];
	x[2] = mlx->t * d[2] - mlx->data.sp->cc[2];
	size = vector_size(x);
	x[0] /= size;
	x[1] /= size;
	x[2] /= size;
	mlx->data.sp->u[0] = (atan2(-1 * x[2], x[0]) + M_PI) / (2 * M_PI);
	mlx->data.sp->u[1] = acos(-1 * x[1]) / (M_PI);
	mlx->data.sp->checker_u[0] = 8 * mlx->data.sp->r * mlx->data.sp->u[0];
	mlx->data.sp->checker_u[1] = 4 * mlx->data.sp->r * mlx->data.sp->u[1];
}

int	check_hit_sp_d(double *d, double *c, t_mlx *mlx)
{
	double	a;
	double	r;

	r = mlx->data.sp->r;
	a = equation_d(pow_2(vector_size(d)), -2 * inner_product(d, c), pow_2(vector_size(c)) - r * r);
	if (a >= 0.000001)
	{
		mlx->t = find_f(pow_2(vector_size(d)), -2 * inner_product(d, c), pow_2(vector_size(c)) - r * r, 1);
		if (mlx->t < 0.0001)
		{
			mlx->t = -2;
			return (0);
		}
		if (mlx->data.sp->mode != NONE)
			uv_axis_sp(d, mlx);
		return (1);
	}
	mlx->t = -2;
	return (0);
}

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

void	updata_normal_vector(double *u, t_img n, double rot[3][3], double *result)
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
	result[0] = inner_product(rot[0], vec);
	result[1] = inner_product(rot[1], vec);
	result[2] = inner_product(rot[2], vec);
}

void	normal_vector_bump(t_mlx *mlx, int i, int j, t_obj obj)
{
	double	rot[3][3];

	bump_rot_data_init(rot, mlx->ray[i][j].n);
	if (obj == SP)
	{
		if (mlx->data.sp->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.sp->u, mlx->data.sp->xpm.normal, rot, mlx->ray[i][j].n);
	}
	else if (obj == CY)
	{
		if (mlx->data.cy->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.cy->u, mlx->data.cy->xpm.normal, rot, mlx->ray[i][j].n);
	}
	else if (obj == CN)
	{
		if (mlx->data.cn->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.cn->u, mlx->data.cn->xpm.normal, rot, mlx->ray[i][j].n);
	}
	
	else if (obj == PL)
	{
		if (mlx->data.pl->mode != BUMP)
			return ;
		updata_normal_vector(mlx->data.pl->u, mlx->data.pl->xpm.normal, rot, mlx->ray[i][j].n);
	}
}

void	push_uv_pl(t_mlx *mlx, double *d, double *x, double *y)
{
	double	dot[3];

	vector_n(d, mlx->t, dot);
	vector_minus(dot, mlx->data.pl->xc, dot);
	mlx->data.pl->u[0] = (fmod(inner_product(x, dot), 1) + 1) / 2;
	mlx->data.pl->u[1] = (fmod(inner_product(y, dot), 1) + 1) / 2;
	mlx->data.pl->checker_u[0] = round(fmod(inner_product(x, dot), 1));
	if (inner_product(x, dot) < 0)
		mlx->data.pl->checker_u[0] -= 1;
	mlx->data.pl->checker_u[1] = round(fmod(inner_product(y, dot), 1));
	if (inner_product(y, dot) < 0)
		mlx->data.pl->checker_u[1] -= 1;
}

void	uv_axis_pl(double *d, t_mlx *mlx)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(mlx->data.pl->nc, z, vec_y);
	cross_product(vec_y, mlx->data.pl->nc, vec_x);
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
	push_uv_pl(mlx, d, vec_x, vec_y);
}

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

void	check_hit_top_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	l[3];
	double	vec[3];
	double	t;

	vector_n(n, mlx->data.cy->h, l);
	vector_plus(l, c, l);
	t = inner_product(n, l) / inner_product(d, n);
	vector_n(d, -t, vec);
	vector_plus(vec, l, vec);
	if (vector_size(vec) < mlx->data.cy->r)
	{
		if (mlx->t < 0.000001 || mlx->t > t)
		{
			mlx->t = t;
			mlx->flag = 3;
		}
	}

}

void	check_hit_bot_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	t;
	double	vec[3];

	t = inner_product(n, c) / inner_product(d, n);
	vector_n(d, -t, vec);
	vector_plus(vec, c, vec);
	if (vector_size(vec) < mlx->data.cy->r)
	{
		if (mlx->t < 0.000001 || mlx->t > t)
		{
			mlx->t = t;
			mlx->flag = 2;
		}
	}
}

int	check_hit_side_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	a;
	double	result1[3];
	double	result2[3];
	double	r;

	r = mlx->data.cy->r;
	cross_product(c, n, result1);
	cross_product(d, n, result2);
	a = equation_d(pow_2(vector_size(result2)), -2 * inner_product(result1, result2), pow_2(vector_size(result1)) - r * r);
	if (a >= 0)
	{
		mlx->t = find_f(pow_2(vector_size(result2)), -2 * inner_product(result1, result2), pow_2(vector_size(result1)) - r * r, 1);
		if (inner_product(d, n) * mlx->t - inner_product(c, n) <= mlx->data.cy->h)
		{
			if (inner_product(d, n) * mlx->t - inner_product(c, n) >= 0.000001)
			{
				mlx->flag = 1;
				return (1);
			}
		}
		mlx->t = -2;
	}
	return (0);
}

int	check_hit_cy_d(double *d, double *n, double *c, t_mlx *mlx)
{
	mlx->flag = 0;
	check_hit_side_cy_d(d, n, c, mlx);
	check_hit_bot_cy_d(d, n, c, mlx);
	check_hit_top_cy_d(d, n, c, mlx);
	return (mlx->flag);
}

void	checker_board(double *uv, unsigned int *rgb)
{
	int	i;
	int	j;

	i = uv[0];
	j = uv[1];
	if ((i + j) % 2 != 0)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else
	{
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	}
}

void	normal_vector_sp(t_mlx *mlx, double	*d, int i, int j)
{
	double	x[3];
	
	x[0] = d[0] * mlx->t - mlx->data.sp->cc[0];
	x[1] = d[1] * mlx->t - mlx->data.sp->cc[1];
	x[2] = d[2] * mlx->t - mlx->data.sp->cc[2];
	normalize_vector(x);
	mlx->ray[i][j].n[0] = x[0];
	mlx->ray[i][j].n[1] = x[1];
	mlx->ray[i][j].n[2] = x[2];
}

void	color_val(unsigned int *rgb, unsigned char *obj_rgb)
{
		rgb[0] = obj_rgb[0];
		rgb[1] = obj_rgb[1];
		rgb[2] = obj_rgb[2];
}

void	xpm_color_select(double *u, unsigned int *rgb, t_img img)
{
	int	i;
	int	j;

	i = u[0] * img.w;
	j = u[1] * img.h;
	hex_to_rgb(img.data[i + img.w * j], rgb);
}

void	color_select(t_mlx *mlx, unsigned int *rgb, t_obj obj)
{
	if (obj == PL)
	{
		if (mlx->data.pl->mode == NONE)
			color_val(rgb, mlx->data.pl->rgb);
		else if (mlx->data.pl->mode == CHECKER)
			checker_board(mlx->data.pl->checker_u, rgb);
		else if (mlx->data.pl->mode == BUMP)
			xpm_color_select(mlx->data.pl->u, rgb, mlx->data.pl->xpm.img);
	}
	else if (obj == CY)
	{
		if (mlx->data.cy->mode == NONE)
			color_val(rgb, mlx->data.cy->rgb);
		else if (mlx->data.cy->mode == CHECKER)
			checker_board(mlx->data.cy->checker_u, rgb);
		else if (mlx->data.cy->mode == BUMP)
			xpm_color_select(mlx->data.cy->u, rgb, mlx->data.cy->xpm.img);
	}
	else if (obj == SP)
	{
		if (mlx->data.sp->mode == NONE)
			color_val(rgb, mlx->data.sp->rgb);
		else if (mlx->data.sp->mode == CHECKER)
			checker_board(mlx->data.sp->checker_u, rgb);
		else if (mlx->data.sp->mode == BUMP)
			xpm_color_select(mlx->data.sp->u, rgb, mlx->data.sp->xpm.img);
	}
	else if (obj == CN)
	{
		if (mlx->data.cn->mode == NONE)
			color_val(rgb, mlx->data.cn->rgb);
		else if (mlx->data.cn->mode == CHECKER)
			checker_board(mlx->data.cn->checker_u, rgb);
		else if (mlx->data.cn->mode == BUMP)
			xpm_color_select(mlx->data.cn->u, rgb, mlx->data.cn->xpm.img);
	}
}

void	check_hit_sp(t_mlx *mlx, double *d, int i, int j)
{
	t_sphere	*save;

	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		if (check_hit_sp_d(d, mlx->data.sp->cc, mlx) == 1)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0.000001)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, SP);
				normal_vector_sp(mlx, d, i, j);
				normal_vector_bump(mlx, i, j, SP);
			}
		}
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
}

void	normal_vector_top_cy(t_mlx *mlx, int i, int j)
{
	vector_copy(mlx->ray[i][j].n, mlx->data.cy->nc);
}

void	normal_vector_bot_cy(t_mlx *mlx, int i, int j)
{
	double	vec[3];

	vector_n(mlx->data.cy->nc, -1, vec);
	vector_copy(mlx->ray[i][j].n, vec);
}

void	normal_vector_cy(t_mlx *mlx, double	*d, int i, int j)
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

void	push_uv_cy_side(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	mlx->data.cy->u[0] = (atan2(inner_product(vec, y), inner_product(vec, x)) + M_PI) / (2 * M_PI);
	mlx->data.cy->u[1] = fmod(inner_product(vec, mlx->data.cy->nc)/ mlx->data.cy->h, 1);
	mlx->data.cy->checker_u[0] = mlx->data.cy->r * 17 * M_PI * (atan2(inner_product(vec, x), inner_product(vec, y)) + M_PI) / (2 * M_PI) / mlx->data.cy->h;
	mlx->data.cy->checker_u[1] = round(fmod(inner_product(vec, mlx->data.cy->nc), 1)) ;
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
	mlx->data.cy->checker_u[0] = round(fmod(inner_product(x, vec) * 2 / mlx->data.cy->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cy->checker_u[0] -= 1;
	mlx->data.cy->checker_u[1] = round(fmod(inner_product(y, vec) * 2 / mlx->data.cy->r, 1));
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
	mlx->data.cy->checker_u[0] = round(fmod(inner_product(x, vec) * 2 / mlx->data.cy->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cy->checker_u[0] -= 1;
	mlx->data.cy->checker_u[1] = round(fmod(inner_product(y, vec) * 2 / mlx->data.cy->r, 1));
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

void	find_cone_head(double *n, double h, double *c, double *result)
{
	vector_n(n, h, result);
	vector_plus(result, c, result);
}

void	check_hit_side_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	head[3];
	double	dot[3];
	double	a[3];
	double	val;
	int		i;

	mlx->t = -2;
	find_cone_head(n, mlx->data.cn->h, c, head);
	val = pow_2(mlx->data.cn->h) / (pow_2(mlx->data.cn->h) + pow_2(mlx->data.cn->r));
	a[0] = pow_2(inner_product(d, n)) - val * pow_2(vector_size(d));
	a[1] = 2 * (val * inner_product(head, d) - (inner_product(d, n) * inner_product(head, n)));
	a[2] = pow_2(inner_product(head, n)) - val * pow_2(vector_size(head));
	if (equation_d(a[0], a[1], a[2]) < 0)
		return ;
	i = 2;
	while (i > 0)
	{
		if (find_f(a[0], a[1], a[2], 2 * i - 3) >= 0)
		{
			vector_n(d, find_f(a[0], a[1], a[2], 2 * i - 3), dot);
			vector_minus(dot, c, dot);
			if (inner_product(dot, n) < mlx->data.cn->h)
			{
				if (inner_product(dot, n) > 0)
				{
					if (mlx->t > find_f(a[0], a[1], a[2], 2 * i - 3) || mlx->t < 0)
						mlx->t = find_f(a[0], a[1], a[2], 2 * i - 3);
					mlx->flag = 1;
				}
			}
		}
		i--;
	}
}

void	check_hit_bot_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	t;
	double	vec[3];

	if (inner_product(d, n) == 0)
		return ;
	t = inner_product(c, n) / inner_product(d, n);
	vector_n(d ,t, vec);
	if (t < EPSILON)
		return ;
	vector_minus(vec, c, vec);
	if (vector_size(vec) <= mlx->data.cn->r)
	{
		if (mlx->t > t || mlx->t < 0)
		{
			mlx->t = t;
			mlx->flag = 2;
		}
	}
}

void	push_uv_cn_side(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];
	double	h;

	h = mlx->data.cn->h;
	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);
	mlx->data.cn->u[0] = (atan2(inner_product(vec, y), inner_product(vec, x)) + M_PI) / (2 * M_PI);
	mlx->data.cn->u[1] = fmod(inner_product(vec, mlx->data.cn->nc) / h, 1);
	mlx->data.cn->checker_u[0] = mlx->data.cn->r * 4 * (atan2(inner_product(vec, x), inner_product(vec, y)) + M_PI) / (2 * M_PI);
	mlx->data.cn->checker_u[1] = round(fmod(inner_product(vec, mlx->data.cn->nc) * 3 / h, 1));
}

void	push_uv_cn_bot(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);	
	mlx->data.cn->u[0] = (fmod(inner_product(x, vec), 1) / 2 + 1) / 2;
	mlx->data.cn->u[1] = (fmod(inner_product(y, vec), 1) / 2 + 1) / 2;
	mlx->data.cn->checker_u[0] = round(fmod(inner_product(x, vec) * 2 / mlx->data.cn->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cn->checker_u[0] -= 1;
	mlx->data.cn->checker_u[1] = round(fmod(inner_product(y, vec) * 2 / mlx->data.cn->r, 1));
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

int	check_hit_cn_d(double *d, double *n, double *c, t_mlx *mlx)
{
	mlx->flag = 0;
	check_hit_side_cn_d(d, n, c, mlx);
	check_hit_bot_cn_d(d, n, c, mlx);
	if (mlx->flag != 0)
		uv_axis_cn(mlx, d);
	return (mlx->flag);
}

void	normal_vector_side_cn(t_mlx *mlx, int i, int j)
{
	double	head[3];
	double	cross_dot_n[3];
	double	cross_x[3];

	find_cone_head(mlx->data.cn->nc, mlx->data.cn->h, mlx->data.cn->cc, head);
	vector_n(mlx->ray[i][j].d, mlx->t, cross_dot_n);
	vector_minus(cross_dot_n, head, cross_dot_n);
	cross_product(cross_dot_n, mlx->data.cn->nc, cross_x);
	cross_product(cross_x, cross_dot_n, mlx->ray[i][j].n);
	normalize_vector(mlx->ray[i][j].n);
}

void	normal_vector_cn(t_mlx *mlx, int i, int j)
{
	if (mlx->flag == 2)
		vector_n(mlx->data.cn->nc, -1, mlx->ray[i][j].n);
	else if (mlx->flag == 1)
		normal_vector_side_cn(mlx, i, j);
}

void	check_hit_cn(t_mlx *mlx, double *d, int i, int j)
{
	t_cone	*save;

	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		normalize_vector(mlx->data.cn->nc);
		if (check_hit_cn_d(d, mlx->data.cn->nc, mlx->data.cn->cc, mlx) != 0)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, CN);
				normal_vector_cn(mlx, i, j);
				normal_vector_bump(mlx, i, j, CN);
			}
		}
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
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

double deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}


void	hit_point(t_mlx *mlx, int i, int j)
{
	double	d[3];

	d[0] = 2 * (double)i * tan(deg_to_rad(mlx->data.cam->fov) / 2) / 1599 - tan(deg_to_rad(mlx->data.cam->fov) / 2);
	d[1] = 9 * (2 * (double)j * tan(deg_to_rad(mlx->data.cam->fov) / 2) / 899 - tan(deg_to_rad(mlx->data.cam->fov) / 2))/16;
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
int	ft_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (-1);
}
void	exec_rot_data(t_mlx *mlx, t_mdata mdata)
{
	updata_rot(mlx, mdata);
}

int	apply_color(unsigned int *rgb)
{
	return (pow_2(256) * rgb[0] + 256 * rgb[1] + rgb[2]);
}

void	ambient_light(t_mlx *mlx, int i, int j, unsigned int *amb)
{
	amb[0] = mlx->data.al->rgb[0] * mlx->ray[i][j].rgb[0] * mlx->data.al->ratio / 255;
	amb[1] = mlx->data.al->rgb[1] * mlx->ray[i][j].rgb[1] * mlx->data.al->ratio / 255;
	amb[2] = mlx->data.al->rgb[2] * mlx->ray[i][j].rgb[2] * mlx->data.al->ratio / 255;
}

void	diffuse_light(t_mlx *mlx, int i, int j, unsigned int *diff)
{
	double	light[3];
	double	res;

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	normalize_vector(mlx->ray[i][j].n);
	res = inner_product(mlx->ray[i][j].n, light);
	if (res < EPSILON)
		res = 0;
	diff[0] = mlx->data.l->rgb[0] * mlx->ray[i][j].rgb[0] * res * mlx->data.l->ratio / 255;
	diff[1] = mlx->data.l->rgb[1] * mlx->ray[i][j].rgb[1] * res * mlx->data.l->ratio / 255;
	diff[2] = mlx->data.l->rgb[2] * mlx->ray[i][j].rgb[2] * res * mlx->data.l->ratio / 255;
}

void	specular_light(t_mlx *mlx, int i, int j, unsigned int *spec)
{
	double	light[3];
	double	val;
	double	n[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	val = inner_product(light, mlx->ray[i][j].n);
	vector_n(mlx->ray[i][j].n, 2 * val, n);
	vector_minus(n, light, light);
	normalize_vector(light);
	vector_n(mlx->ray[i][j].d, -1, n);
	val = inner_product(n, light);
	if (val < EPSILON)
		val = 0;
	val = pow(val, 10);
	spec[0] = 4 * mlx->data.l->rgb[0] * mlx->ray[i][j].rgb[0] * mlx->data.al->ratio * val / 255;
	spec[1] = 4 * mlx->data.l->rgb[1] * mlx->ray[i][j].rgb[1] * mlx->data.al->ratio * val / 255;
	spec[2] = 4 * mlx->data.l->rgb[2] * mlx->ray[i][j].rgb[2] * mlx->data.al->ratio * val / 255;
	// spec[0] = 255 * val;
	// spec[1] = 255 * val;
	// spec[2] = 255 * val;
}

void	reset_phong_light(unsigned int phong[3][3])
{
	phong[1][0] = 0;
	phong[1][1] = 0;
	phong[1][2] = 0;
	phong[2][0] = 0;
	phong[2][1] = 0;
	phong[2][2] = 0;
}

int	check_hit_gray_sp_d(double *d, double *dot, t_mlx *mlx)
{
	double	exist;
	double	a[3];
	double	t;
	double	mid[3];
	double	result;

	if (vector_size(d) < 0.0001)
		return (0);
	vector_copy(mid, mlx->data.sp->cc);
	vector_minus(dot, mid, mid);
	result = inner_product(d, mid);
	a[0] = pow_2(vector_size(d));
	a[1] = 2 * result;
	a[2] = pow_2(vector_size(mid)) - pow_2(mlx->data.sp->r);
	exist = equation_d(a[0], a[1], a[2]);
	if (exist >= 0.0000001)
	{
		t = find_f(a[0], a[1], a[2], a[0]);
		if (t < 0.0001)
			return (0);
		return (1);
	}
	return (0);
}

int	check_hit_gray_sp(t_mlx *mlx, int i, int j)
{
	t_sphere	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		if (check_hit_gray_sp_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.sp = save;
			return (1);
		}
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
	return (0);
}

int	check_hit_gray_cy_top_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	c[3];
	double	t;

	vector_n(mlx->data.cy->nc, mlx->data.cy->h, c);
	vector_plus(c, mlx->data.cy->cc, c);
	vector_minus(c, dot, vec);
	if (inner_product(d, mlx->data.cy->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cy->nc) / inner_product(d, mlx->data.cy->nc);
	if (t < 0.000001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, c, vec);
	if (vector_size(vec) > mlx->data.cy->r)
		return (0);
	return (1);
}

int	check_hit_gray_cy_bot_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	t;

	vector_minus(mlx->data.cy->cc, dot, vec);
	if (inner_product(d, mlx->data.cy->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cy->nc) / inner_product(d, mlx->data.cy->nc);
	if (t < 0.000001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	if (vector_size(vec) > mlx->data.cy->r)
		return (0);
	return (1);
}

int	check_hit_gray_cy_side_d(double *d, double *dot, t_mlx *mlx)
{
	double	cross_d_n[3];
	double	cross_dot_c_n[3];
	double	vec[3];
	double	t;

	vector_minus(dot, mlx->data.cy->cc, vec);
	cross_product(d, mlx->data.cy->nc, cross_d_n);
	cross_product(vec, mlx->data.cy->nc, cross_dot_c_n);
	t = mlx->data.cy->r;
	if (equation_d(pow_2(vector_size(cross_d_n)), 2 * inner_product(cross_dot_c_n, cross_d_n), pow_2(vector_size(cross_dot_c_n)) - pow_2(t)) < 0)
		return (0);
	t = find_f(pow_2(vector_size(cross_d_n)), 2 * inner_product(cross_dot_c_n, cross_d_n), pow_2(vector_size(cross_dot_c_n)) - pow_2(t), 1);
	if (t < 0.00000001)
		return (0);
	if (inner_product(d, mlx->data.cy->nc) * t + inner_product(vec, mlx->data.cy->nc) < mlx->data.cy->h)
	{
		if (inner_product(d, mlx->data.cy->nc) * t + inner_product(vec, mlx->data.cy->nc) > 0)
			return (1);
	}
	return (0);
}

int	check_hit_gray_cy_d(double *d, double *dot, t_mlx *mlx)
{
	if (check_hit_gray_cy_top_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cy_bot_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cy_side_d(d, dot, mlx) == 1)
		return (1);
	return (0);
}

int	check_hit_gray_cy(t_mlx *mlx, int i, int j)
{
	t_cylinder	*save;
	double		light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.cy;
	while (mlx->data.cy != NULL)
	{
		if (check_hit_gray_cy_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.cy = save;
			return (1);
		}
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
	return (0);
}

int	check_hit_gray_pl_d(double *d, double *dot, t_mlx *mlx)
{
	double	t;

	if (inner_product(d, mlx->data.pl->nc) < 0.000001)
		return (0);
	t = (inner_product(mlx->data.pl->nc, mlx->data.pl->xc) - inner_product(dot, mlx->data.pl->nc)) / inner_product(d, mlx->data.pl->nc);
	if (t <= 0.000001)
		return (0);
	return (1);
}

int	check_hit_gray_pl(t_mlx *mlx, int i, int j)
{
	t_plane	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.pl;
	while (mlx->data.pl != NULL)
	{
		if (check_hit_gray_pl_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.pl = save;
			return (1);
		}
		mlx->data.pl = mlx->data.pl->next;
	}
	mlx->data.pl = save;
	return (0);
}

int	check_hit_gray_cn_bot_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	t;

	vector_minus(mlx->data.cn->cc, dot, vec);
	if (inner_product(d, mlx->data.cn->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cn->nc) / inner_product(d, mlx->data.cn->nc);
	if (t < 0.0001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, mlx->data.cn->cc, vec);
	if (vector_size(vec) > mlx->data.cn->r)
		return (0);
	return (1);	
}

int	check_hit_gray_cn_side_d(double *d, double *dot, t_mlx *mlx)
{
	double	head[3];
	double	vec[3];
	double	a[3];
	double	val;
	int		k;

	find_cone_head(mlx->data.cn->nc, mlx->data.cn->h, mlx->data.cn->cc, head);
	vector_minus(head, dot, head);
	val = (pow_2(mlx->data.cn->h) / (pow_2(mlx->data.cn->h) + pow_2(mlx->data.cn->r)));
	a[0] = pow_2(inner_product(d, mlx->data.cn->nc)) - val * pow_2(vector_size(d));
	a[1] = 2 * (val * inner_product(head, d) - (inner_product(d, mlx->data.cn->nc) * inner_product(head, mlx->data.cn->nc)));
	a[2] = pow_2(inner_product(head, mlx->data.cn->nc)) - val * pow_2(vector_size(head));
	if (equation_d(a[0], a[1], a[2]) < 0)
		return (0);
	k = 2;
	while (k > 0)
	{
		if (find_f(a[0], a[1], a[2], 2 * k - 3) > 0.001)
		{
			vector_n(d, find_f(a[0], a[1], a[2], 2 * k - 3), vec);
			vector_plus(vec, dot, vec);
			vector_minus(vec, mlx->data.cn->cc, vec);
			if (inner_product(vec, mlx->data.cn->nc) < mlx->data.cn->h)
			{
				if (inner_product(vec, mlx->data.cn->nc) > 0)
					return (1);
			}
		}
		k--;
	}
	return (0);
}

int	check_hit_gray_cn_d(double *d, double *dot, t_mlx *mlx)
{
	if (check_hit_gray_cn_bot_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cn_side_d(d, dot, mlx) == 1)
		return (1);
	return (0);
}

int	check_hit_gray_cn(t_mlx *mlx, int i, int j)
{
	t_cone	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		if (check_hit_gray_cn_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.cn = save;
			return (1);
		}
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
	return (0);
}


void	gray_exist(t_mlx *mlx, int i, int j, unsigned int phong[3][3])
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

void	phong_reset(unsigned int phong[3][3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			phong[i][j]= 0;
			j++;
		}
		i++;
	}
}

void	sum_color(t_mlx *mlx, int i, int j, unsigned int phong[3][3])
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
void	phong_point(t_mlx *mlx, int i, int j)
{
	unsigned int	phong[3][3];
	t_light			*save;
	int				k;

	save = mlx->data.l;
	phong_reset(phong);
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

void	find_ray_dot(t_mlx *mlx, int i, int j)
{	
	mlx->ray[i][j].dot[0] = mlx->ray[i][j].deep * mlx->ray[i][j].d[0]; 
	mlx->ray[i][j].dot[1] = mlx->ray[i][j].deep * mlx->ray[i][j].d[1];
	mlx->ray[i][j].dot[2] = mlx->ray[i][j].deep * mlx->ray[i][j].d[2];
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

int	loop_main(t_mlx *mlx)
{
	t_mdata	rot;
	
	static int	i = 0;
	if (i == 0)
	{
		// test(mlx->data);
		copy_rot_data(mlx);
		rot = data_cam_num_init(*mlx);
		exec_rot_data(mlx, rot);
		ctest(mlx->data);
		canvas_match(mlx);
		phong_init(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
		i++;
	}
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