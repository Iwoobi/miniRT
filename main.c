/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:43:50 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 22:12:19 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


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