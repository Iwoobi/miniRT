/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:43:50 by youhan            #+#    #+#             */
/*   Updated: 2022/10/31 03:37:48 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rot_data(t_mdata data)
{
	int	i;
	int	j;

	printf("rot_data\n");
	printf("%f  %f   %f\n",data.m[0], data.m[1], data.m[2]);

	i = 0;
	while (i < 3)
	{
		j=0;
		while (j < 3)
		{
			printf("%f ", data.rot[3 * i + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


void	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit(-1);
}

void	check_format(char *argv, char *format)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	j = 0;
	cnt = 0;
	while (argv[i])
		i++;
	while (format[j])
		j++;
	i--;
	j--;
	while (cnt <= j)
	{
		if (argv[i] != format[j - cnt])
			print_error("check file name");
		i--;
		cnt++;
	}
}

int	opne_data(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		print_error("check file name");
	return (fd);
}

int	div_str(char *str, char *div)
{
	if (*str == '\0')
		return (-1);
	if (str == NULL || div == NULL)
		return (-1);
	while (*div != '\0')
	{
		if (*div != *str)
			return (-1);
		div++;
		str++;
	}
	if (*str == ' ' || *str == '\n' || *str == '\0')
		return (1);
	return (-1);
}

void	push_x_y_z(double *data, char **str)
{
	int	i;
	int	count;

	i = 0;
	while (i < 3)
	{
		count = 0;
		data[i] = ft_char_double(*str, &count);
		*str += count;
		if (**str != ',' && i != 2)
			print_error("check data");
		if (i != 2)
			(*str)++;
		i++;
	}
}

void	open_xpm_file(t_img *img, char *file_name, t_mlx *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx->mlx, file_name, \
										&(img->w), &(img->h));
	if (img->img == NULL)
		print_error("couldn't open xpm file.");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
											&img->size_l, &img->endian);
}

void	remove_newline(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 1] == '\n')
		file_name[i - 1] = '\0';
}

int	check_file_number(char **file_name)
{
	int	cnt;

	cnt = 0;
	while (file_name[cnt])
		cnt++;
	if (cnt == 3)
	{
		remove_newline(file_name[2]);
		return (1);
	}
	return (0);
}

t_texture	push_xpm(t_xpm *xpm, char **str, t_mlx *mlx)
{
	char	**file_name;

	file_name = ft_split(*str, ' ');
	if (file_name == NULL)
		print_error("malloc error.");
	if (file_name[1] == NULL || file_name[2] == NULL)
		print_error("need both image and normal file.");
	if (!check_file_number(file_name))
		print_error("need only two files.");
	check_format(file_name[1], ".xpm");
	check_format(file_name[2], ".xpm");
	open_xpm_file(&(xpm->img), file_name[1], mlx);
	open_xpm_file(&(xpm->normal), file_name[2], mlx);
	while (**str != '\n' && **str != '\0')
		(*str)++;
	return (BUMP);

}

t_texture	push_rgb(unsigned char *rgb, char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((**str >= 9 && **str <= 13) || **str == 32)
	{
		(*str)++;
		count++;
	}
	if (div_str(*str, "checker") == 1)
	{
		*str += 7;
		return (CHECKER);
	}
	while (i < 3)
	{
		count = 0;
		rgb[i] = (unsigned char)ft_char_double(*str, &count);
		*str += count;
		if (**str != ',' && i != 2)
			print_error("check , data");
		if (i != 2)
			(*str)++;
		i++;
	}
	return (NONE);
}

void	null_check(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != '\0')
	{
		printf("error : %s\n", str);
		print_error("check input data");
	}
}

void	push_a(char *str, t_mlx *mlx)
{
	int			count;
	t_alight	*save;

	save = mlx->data.al;
	count = 0;
	str++;
	while (mlx->data.num.count_al > count)
	{
		if (mlx->data.num.count_al - count == 1)
		{
			mlx->data.al->next = (t_alight *)malloc(sizeof(t_alight) * 1);
			if (mlx->data.al->next == NULL)
				print_error("malloc error");
			mlx->data.al->next->next = NULL;
		}
		mlx->data.al = mlx->data.al->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_al += 1;
	mlx->data.al->ratio = ft_char_double(str, &count);
	str += count;
	push_rgb(&(mlx->data.al->rgb[0]), &str);
	null_check(str);
	mlx->data.al = save;
}

void	push_c(char *str, t_mlx *mlx)
{
	int		count;
	t_cam	*save;

	save = mlx->data.cam;
	count = 0;
	str += 1;
	while (mlx->data.num.count_cam > count)
	{
		if (mlx->data.num.count_cam - count == 1)
		{
			mlx->data.cam->next = (t_cam *)malloc(sizeof(t_cam) * 1);
			if (mlx->data.cam->next == NULL)
				print_error("malloc error");
			mlx->data.cam->next->next = NULL;
		}
		mlx->data.cam = mlx->data.cam->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_cam += 1;
	push_x_y_z(&(mlx->data.cam->x[0]), &str);
	push_x_y_z(&(mlx->data.cam->n[0]), &str);
	mlx->data.cam->fov = ft_char_double(str, &count);
	str += count;
	null_check(str);
	mlx->data.cam = save;
}

void	push_l(char *str, t_mlx *mlx)
{
	int		count;
	t_light	*save;

	save = mlx->data.l;
	count = 0;
	str++;
	while (mlx->data.num.count_l > count)
	{
		if (mlx->data.num.count_l - count == 1)
		{
			mlx->data.l->next = (t_light *)malloc(sizeof(t_light) * 1);
			if (mlx->data.l->next == NULL)
				print_error("malloc error");
			mlx->data.l->next->next = NULL;
		}
		mlx->data.l = mlx->data.l->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_l += 1;
	push_x_y_z(&(mlx->data.l->x[0]), &str);
	mlx->data.l->ratio = ft_char_double(str, &count);
	str += count;
	push_rgb(&(mlx->data.l->rgb[0]), &str);
	null_check(str);
	mlx->data.l = save;
}

void	push_sp(char *str, t_mlx *mlx)
{
	int			count;
	t_sphere	*save;

	save = mlx->data.sp;
	count = 0;
	str += 2;
	while (mlx->data.num.count_sp > count)
	{
		if (mlx->data.num.count_sp - count == 1)
		{
			mlx->data.sp->next = (t_sphere *)malloc(sizeof(t_sphere) * 1);
			if (mlx->data.sp->next == NULL)
				print_error("malloc error");
			mlx->data.sp->next->next = NULL;
		}
		mlx->data.sp = mlx->data.sp->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_sp += 1;
	push_x_y_z(&(mlx->data.sp->c[0]), &str);
	mlx->data.sp->r = ft_char_double(str, &count);
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.sp->mode = push_xpm(&(mlx->data.sp->xpm), &str, mlx);
	else
		mlx->data.sp->mode = push_rgb(&(mlx->data.sp->rgb[0]), &str);
	null_check(str);
	mlx->data.sp = save;
}

int	check_bump_word(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (div_str(&(str[i]),"bump"));
}

void	push_pl(char *str, t_mlx *mlx)
{
	int		count;
	t_plane	*save;

	save = mlx->data.pl;
	count = 0;
	str += 2;
	while (mlx->data.num.count_pl > count)
	{
		if (mlx->data.num.count_pl - count == 1)
		{
			mlx->data.pl->next = (t_plane *)malloc(sizeof(t_plane) * 1);
			if (mlx->data.pl->next == NULL)
				print_error("malloc error");
			mlx->data.pl->next->next = NULL;
		}
		mlx->data.pl = mlx->data.pl->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_pl += 1;
	push_x_y_z(&(mlx->data.pl->x[0]), &str);
	push_x_y_z(&(mlx->data.pl->n[0]), &str);
	if (check_bump_word(str) == 1)
		mlx->data.pl->mode = push_xpm(&(mlx->data.pl->xpm), &str, mlx);
	else
		mlx->data.pl->mode = push_rgb(&(mlx->data.pl->rgb[0]), &str);
	null_check(str);
	mlx->data.pl = save;
}

double	pow_2(double a)
{
	return (a * a);
}

void	push_cy(char *str, t_mlx *mlx)
{
	int		count;
	t_cylinder	*save;

	save = mlx->data.cy;
	count = 0;
	str += 2;
	while (mlx->data.num.count_cy > count)
	{
		if (mlx->data.num.count_cy - count == 1)
		{
			mlx->data.cy->next = (t_cylinder *)malloc(sizeof(t_cylinder) * 1);
			if (mlx->data.cy->next == NULL)
				print_error("malloc error");
			mlx->data.cy->next->next = NULL;
		}
		mlx->data.cy = mlx->data.cy->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_cy += 1;
	push_x_y_z(&(mlx->data.cy->c[0]), &str);
	push_x_y_z(&(mlx->data.cy->n[0]), &str);
	mlx->data.cy->r = ft_char_double(str, &count);
	str += count;
	count = 0;
	mlx->data.cy->h = ft_char_double(str, &count);
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.cy->mode = push_xpm(&(mlx->data.cy->xpm), &str, mlx);
	else
		mlx->data.cy->mode = push_rgb(&(mlx->data.cy->rgb[0]), &str);
	null_check(str);
	mlx->data.cy = save;
}

void	push_cr(char *str, t_mlx *mlx)
{
	int		count;
	t_cron	*save;

	save = mlx->data.cr;
	count = 0;
	str += 2;
	while (mlx->data.num.count_cr > count)
	{
		if (mlx->data.num.count_cr - count == 1)
		{
			mlx->data.cr->next = (t_cron *)malloc(sizeof(t_cron) * 1);
			if (mlx->data.cr->next == NULL)
				print_error("malloc error");
			mlx->data.cr->next->next = NULL;
		}
		mlx->data.cr = mlx->data.cr->next;
		count++;
	}
	count = 0;
	mlx->data.num.count_cr += 1;
	push_x_y_z(&(mlx->data.cr->c[0]), &str);
	push_x_y_z(&(mlx->data.cr->n[0]), &str);
	mlx->data.cr->r = ft_char_double(str, &count);
	str += count;
	count = 0;
	mlx->data.cr->h = ft_char_double(str, &count);
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.cr->mode = push_xpm(&(mlx->data.cr->xpm), &str, mlx);
	else
		mlx->data.cr->mode = push_rgb(&(mlx->data.cr->rgb[0]), &str);
	null_check(str);
	mlx->data.cr = save;
}

void	check_obj(char *str, t_mlx *mlx)
{
	if (div_str(str, "A") == 1)
		push_a(str, mlx);
	else if (div_str(str, "C") == 1)
		push_c(str, mlx);
	else if (div_str(str, "L") == 1)
		push_l(str, mlx);
	else if (div_str(str, "sp") == 1)
		push_sp(str, mlx);
	else if (div_str(str, "pl") == 1)
		push_pl(str, mlx);
	else if (div_str(str, "cy") == 1)
		push_cy(str, mlx);
	else if (div_str(str, "cr") == 1)
		push_cr(str, mlx);
	else if (*str != '\0')
	{
		printf("here\n");
		printf("\n%s\n", str);
		print_error("check data");
	}
}

void	check_push_data(char *str, t_mlx *mlx)
{
	check_obj(str, mlx);
}

void	push_data(int fd, t_mlx *mlx)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (!(*str == '\n' && ft_strlen(str) == 1))
			check_push_data(str, mlx);
		free(str);
		str = get_next_line(fd);
	}
}

void	close_non_data(t_mlx *mlx)
{
	if (mlx->data.num.count_al == 0)
	{
		free(mlx->data.al);
		mlx->data.al = NULL;
	}
	if (mlx->data.num.count_cy == 0)
	{
		free(mlx->data.cy);
		mlx->data.cy = NULL;
	}
	if (mlx->data.num.count_l == 0)
	{
		free(mlx->data.l);
		mlx->data.l = NULL;
	}
	if (mlx->data.num.count_pl == 0)
	{
		free(mlx->data.pl);
		mlx->data.pl = NULL;
	}
	if (mlx->data.num.count_sp == 0)
	{
		free(mlx->data.sp);
		mlx->data.sp = NULL;
	}
	if (mlx->data.num.count_cr == 0)
	{
		free(mlx->data.cr);
		mlx->data.cr = NULL;
	}
}

void	check_cam_error(t_mlx *mlx)
{
	if (mlx->data.num.count_cam == 0)
		print_error("check cam data");
}

void	check_input(char *argv, t_mlx *mlx)
{
	check_format(argv, ".rt");
	push_data(opne_data(argv), mlx);
	close_non_data(mlx);
	check_cam_error(mlx);
}

void	init_mlx_data(t_mlx *mlx)
{
	int	i;
	mlx->size[0] = 1600;
	mlx->size[1] = 900;
	mlx->cam_num = 0;
	mlx->data.num.count_l = 0;
	mlx->data.num.count_al = 0;
	mlx->data.num.count_cam = 0;
	mlx->data.num.count_sp = 0;
	mlx->data.num.count_pl = 0;
	mlx->data.num.count_cy = 0;
	mlx->data.num.count_cr = 0;
	mlx->ray = (t_ray **)malloc(sizeof(t_ray *) * 1600);
	if (mlx->ray == NULL)
		print_error("malloc error");
	i = 0;
	while (i < 1600)
	{
		mlx->ray[i] = malloc(sizeof(t_ray) * 900);
		if (mlx->ray[i] == NULL)
			print_error("malloc error");
		i++;
	}
	mlx->data.cr = (t_cron *)malloc(sizeof(t_cron) * 1);
	mlx->data.al = (t_alight *)malloc(sizeof(t_alight) * 1);
	mlx->data.cam = (t_cam *)malloc(sizeof(t_cam) * 1);
	mlx->data.l = (t_light *)malloc(sizeof(t_light) * 1);
	mlx->data.pl = (t_plane *)malloc(sizeof(t_plane) * 1);
	mlx->data.cy = (t_cylinder *)malloc(sizeof(t_cylinder) * 1);
	mlx->data.sp = (t_sphere *)malloc(sizeof(t_sphere) * 1);
	if (mlx->data.al == NULL || mlx->data.cam == NULL || mlx->data.l == NULL)
		print_error("malloc error");
	if (mlx->data.pl == NULL || mlx->data.cy == NULL || mlx->data.sp == NULL)
		print_error("malloc error");
	if (mlx->data.cr == NULL)
		print_error("malloc error");
	mlx->data.al->next = NULL;
	mlx->data.cr->next = NULL;
	mlx->data.l->next = NULL;
	mlx->data.cam->next = NULL;
	mlx->data.pl->next = NULL;
	mlx->data.cy->next = NULL;
	mlx->data.sp->next = NULL;
}

int	press_key(int key_code)
{
	if (key_code == 53)
		exit(0);
	return (1);
}

double	inner_product(double *u, double *w)
{
	return (u[0] * w[0] + u[1] * w[1] + u[2] * w[2]);
}

void	cross_product(double *u, double *w, double *result)
{
	result[0] = u[1] * w[2] - u[2] * w[1];
	result[1] = u[2] * w[0] - u[0] * w[2];
	result[2] = u[0] * w[1] - u[1] * w[0];
}

double	vector_size(double *x)
{
	return (sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]));
}

void	vector_n(double *x, double val, double *result)
{
	result[0] = x[0] * val;
	result[1] = x[1] * val;
	result[2] = x[2] * val;
}

void	vector_plus(double *x, double *y, double *result)
{
	result[0] = x[0] + y[0];
	result[1] = x[1] + y[1];
	result[2] = x[2] + y[2];
}

void	vector_minus(double *x, double *y, double *result)
{
	result[0] = x[0] - y[0];
	result[1] = x[1] - y[1];
	result[2] = x[2] - y[2];
}

void	vector_copy(double *x, double *copy)
{
	x[0] = copy[0];
	x[1] = copy[1];
	x[2] = copy[2];
}

void	normalize_vector(double *vec)
{
	double	size;

	size = vector_size(vec);
	vec[0] /= size;
	vec[1] /= size;
	vec[2] /= size;
}

double	equation_d(double a, double b, double c)
{
	return(pow_2(b) - 4 * (a * c));
}

double	find_f(double a, double b, double c, double flag)
{
	if (flag > 0)
		return ((-b - sqrt(equation_d(a, b, c))) / (2 * a));
	else
		return ((-b + sqrt(equation_d(a, b, c))) / (2 * a));
}

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
			print_error("check cam rotate");
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

void	updata_rot_cr(t_data *data, t_mdata mdata)
{
	t_cron	*save;

	save = data->cr;
	while (data->cr != NULL)
	{
		data->cr->cc[0] -= mdata.m[0];
		data->cr->cc[1] -= mdata.m[1];
		data->cr->cc[2] -= mdata.m[2];
		trans_rot_data(data->cr->cc, mdata);
		trans_rot_data(data->cr->nc, mdata);
		data->cr = data->cr->next;
	}
	data->cr = save;
}


void	updata_rot(t_mlx *mlx, t_mdata mdata)
{
	updata_rot_l(&(mlx->data), mdata);
	updata_rot_sp(&(mlx->data), mdata);
	updata_rot_pl(&(mlx->data), mdata);
	updata_rot_cy(&(mlx->data), mdata);
	updata_rot_cr(&(mlx->data), mdata);
}

void	test(t_data mlx)
{
	test_a(mlx);
	test_c(mlx);
	test_l(mlx);
	test_cy(mlx);
	test_cr(mlx);
	test_pl(mlx);
	test_sp(mlx);
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

void	copy_rot_cr(t_mlx *mlx)
{
	t_cron	*save;

	save = mlx->data.cr;
	while (mlx->data.cr != NULL)
	{
		mlx->data.cr->cc[0] = mlx->data.cr->c[0];
		mlx->data.cr->cc[1] = mlx->data.cr->c[1];
		mlx->data.cr->cc[2] = mlx->data.cr->c[2];
		mlx->data.cr->nc[0] = mlx->data.cr->n[0];
		mlx->data.cr->nc[1] = mlx->data.cr->n[1];
		mlx->data.cr->nc[2] = mlx->data.cr->n[2];
		mlx->data.cr = mlx->data.cr->next;
	}
	mlx->data.cr = save;
}

void	copy_rot_data(t_mlx *mlx)
{
	copy_rot_l(mlx);
	copy_rot_sp(mlx);
	copy_rot_pl(mlx);
	copy_rot_cy(mlx);
	copy_rot_cr(mlx);
}

void	ctest(t_data mlx)
{
	ctest_cy(mlx);
	ctest_cr(mlx);
	ctest_l(mlx);
	ctest_pl(mlx);
	ctest_sp(mlx);
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
	mlx->data.sp->checker_u[0] = 2 * mlx->data.sp->r * mlx->data.sp->u[0];
	mlx->data.sp->checker_u[1] = mlx->data.sp->r * mlx->data.sp->u[1];
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

void	hex_to_rgb(int hex, unsigned int *rgb)
{
	rgb[2] = hex % 256;
	hex /= 256;
	rgb[1] = hex % 256;
	hex /= 256;
	rgb[0] = hex;
}

void	xpm_color_select_sp(t_sphere *sp, unsigned int *rgb)
{
	double	i;
	double	j;

	i = (sp->u[0]) / (M_PI);
	j = (sp->u[1]) / (M_PI);
	hex_to_rgb(sp->xpm.img.data[(int)(i * sp->xpm.img.w) + sp->xpm.img.w * (int)(j * sp->xpm.img.h)], rgb);
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
			xpm_color_select_sp(mlx->data.sp, rgb);
	}
	else if (obj == CY)
	{
		if (mlx->data.cy->mode == NONE)
			color_val(rgb, mlx->data.cy->rgb);
		else if (mlx->data.cy->mode == CHECKER)
			checker_board(mlx->data.cy->checker_u, rgb);
		else if (mlx->data.cy->mode == BUMP)
			xpm_color_select_sp(mlx->data.sp, rgb);
	}
	else if (obj == SP)
	{
		if (mlx->data.sp->mode == NONE)
			color_val(rgb, mlx->data.sp->rgb);
		else if (mlx->data.sp->mode == CHECKER)
			checker_board(mlx->data.sp->checker_u, rgb);
		else if (mlx->data.sp->mode == BUMP)
			xpm_color_select_sp(mlx->data.sp, rgb);
	}
	else if (obj == CR)
	{
		if (mlx->data.cr->mode == NONE)
			color_val(rgb, mlx->data.cr->rgb);
		else if (mlx->data.cr->mode == CHECKER)
			checker_board(mlx->data.cr->checker_u, rgb);
		else if (mlx->data.cr->mode == BUMP)
			xpm_color_select_sp(mlx->data.sp, rgb);
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
	double	h;

	h = mlx->data.cy->h;
	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cy->cc, vec);
	mlx->data.cy->u[0] = (atan2(inner_product(vec, y), inner_product(vec, x)) + M_PI) / (2 * M_PI);
	mlx->data.cy->u[1] = fmod(inner_product(vec, mlx->data.cy->nc), 1);
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
	printf("asd\n");
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
			}
		}
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
}

void	find_cron_head(double *n, double h, double *c, double *result)
{
	vector_n(n, h, result);
	vector_plus(result, c, result);
}

void	check_hit_side_cr_d(double *d, double *n, double *c, t_mlx *mlx)
{
	double	head[3];
	double	dot[3];
	double	a[3];
	double	val;
	int		i;

	mlx->t = -2;
	find_cron_head(n, mlx->data.cr->h, c, head);
	val = pow_2(mlx->data.cr->h) / (pow_2(mlx->data.cr->h) + pow_2(mlx->data.cr->r));
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
			if (inner_product(dot, n) < mlx->data.cr->h)
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

void	check_hit_bot_cr_d(double *d, double *n, double *c, t_mlx *mlx)
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
	if (vector_size(vec) <= mlx->data.cr->r)
	{
		if (mlx->t > t || mlx->t < 0)
		{
			mlx->t = t;
			mlx->flag = 2;
		}
	}
}

void	push_uv_cr_side(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];
	double	h;

	h = mlx->data.cr->h;
	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cr->cc, vec);
	mlx->data.cr->u[0] = (atan2(inner_product(vec, y), inner_product(vec, x)) + M_PI) / (2 * M_PI);
	mlx->data.cr->u[1] = fmod(inner_product(vec, mlx->data.cr->nc), 1);
	mlx->data.cr->checker_u[0] = mlx->data.cr->r * 4 * (atan2(inner_product(vec, x), inner_product(vec, y)) + M_PI) / (2 * M_PI);
	mlx->data.cr->checker_u[1] = round(fmod(inner_product(vec, mlx->data.cr->nc) * 3 / h, 1));
}

void	push_uv_cr_bot(t_mlx *mlx, double *d, double *x, double *y)
{
	double	vec[3];

	vector_n(d, mlx->t, vec);
	vector_minus(vec, mlx->data.cr->cc, vec);	
	mlx->data.cr->u[0] = (fmod(inner_product(x, vec), 1) + 1) / 2;
	mlx->data.cr->u[1] = (fmod(inner_product(y, vec), 1) + 1) / 2;
	mlx->data.cr->checker_u[0] = round(fmod(inner_product(x, vec) * 2 / mlx->data.cr->r, 1));
	if (inner_product(x, vec) < 0)
		mlx->data.cr->checker_u[0] -= 1;
	mlx->data.cr->checker_u[1] = round(fmod(inner_product(y, vec) * 2 / mlx->data.cr->r, 1));
	if (inner_product(y, vec) < 0)
		mlx->data.cr->checker_u[1] -= 1;
}

void	push_uv_cr(t_mlx *mlx, double *d, double *x, double *y)
{
	if (mlx->flag == 1)
		push_uv_cr_side(mlx, d, x, y);
	else if (mlx->flag == 2)
		push_uv_cr_bot(mlx, d, x, y);
}

void	uv_axis_cr(t_mlx *mlx, double *d)
{
	double	vec_y[3];
	double	vec_x[3];
	double	z[3];

	axis_z(z);
	cross_product(mlx->data.cr->nc, z, vec_y);
	cross_product(vec_y, mlx->data.cr->nc, vec_x);
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
	push_uv_cr(mlx, d, vec_x, vec_y);
}

int	check_hit_cr_d(double *d, double *n, double *c, t_mlx *mlx)
{
	mlx->flag = 0;
	check_hit_side_cr_d(d, n, c, mlx);
	check_hit_bot_cr_d(d, n, c, mlx);
	if (mlx->flag != 0)
		uv_axis_cr(mlx, d);
	return (mlx->flag);
}

void	normal_vector_side_cr(t_mlx *mlx, int i, int j)
{
	double	head[3];
	double	cross_dot_n[3];
	double	cross_x[3];

	find_cron_head(mlx->data.cr->nc, mlx->data.cr->h, mlx->data.cr->cc, head);
	vector_n(mlx->ray[i][j].d, mlx->t, cross_dot_n);
	vector_minus(cross_dot_n, head, cross_dot_n);
	cross_product(cross_dot_n, mlx->data.cr->nc, cross_x);
	cross_product(cross_x, cross_dot_n, mlx->ray[i][j].n);
	normalize_vector(mlx->ray[i][j].n);
}

void	normal_vector_cr(t_mlx *mlx, int i, int j)
{
	if (mlx->flag == 2)
		vector_n(mlx->data.cr->nc, -1, mlx->ray[i][j].n);
	else if (mlx->flag == 1)
		normal_vector_side_cr(mlx, i, j);
}

void	check_hit_cr(t_mlx *mlx, double *d, int i, int j)
{
	t_cron	*save;

	save = mlx->data.cr;
	while (mlx->data.cr != NULL)
	{
		normalize_vector(mlx->data.cr->nc);
		if (check_hit_cr_d(d, mlx->data.cr->nc, mlx->data.cr->cc, mlx) != 0)
		{
			if (mlx->ray[i][j].deep > mlx->t || mlx->ray[i][j].deep < 0)
			{
				mlx->ray[i][j].deep = mlx->t;
				color_select(mlx, mlx->ray[i][j].rgb, CR);
				normal_vector_cr(mlx, i, j);
			}
		}
		mlx->data.cr = mlx->data.cr->next;
	}
	mlx->data.cr = save;
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
	check_hit_cr(mlx, d, i, j); 
}

void	canvas_match(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1600)
	{
		j = 0;
		while (j < 900)
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

int	check_hit_gray_cr_bot_d(double *d, double *dot, t_mlx *mlx)
{
	double	vec[3];
	double	t;

	vector_minus(mlx->data.cr->cc, dot, vec);
	if (inner_product(d, mlx->data.cr->nc) < 0.000001)
		return (0);
	t = inner_product(vec, mlx->data.cr->nc) / inner_product(d, mlx->data.cr->nc);
	if (t < 0.0001)
		return (0);
	vector_n(d, t, vec);
	vector_plus(vec, dot, vec);
	vector_minus(vec, mlx->data.cr->cc, vec);
	if (vector_size(vec) > mlx->data.cr->r)
		return (0);
	return (1);	
}

int	check_hit_gray_cr_side_d(double *d, double *dot, t_mlx *mlx)
{
	double	head[3];
	double	vec[3];
	double	a[3];
	double	val;
	int		k;

	find_cron_head(mlx->data.cr->nc, mlx->data.cr->h, mlx->data.cr->cc, head);
	vector_minus(head, dot, head);
	val = (pow_2(mlx->data.cr->h) / (pow_2(mlx->data.cr->h) + pow_2(mlx->data.cr->r)));
	a[0] = pow_2(inner_product(d, mlx->data.cr->nc)) - val * pow_2(vector_size(d));
	a[1] = 2 * (val * inner_product(head, d) - (inner_product(d, mlx->data.cr->nc) * inner_product(head, mlx->data.cr->nc)));
	a[2] = pow_2(inner_product(head, mlx->data.cr->nc)) - val * pow_2(vector_size(head));
	if (equation_d(a[0], a[1], a[2]) < 0)
		return (0);
	k = 2;
	while (k > 0)
	{
		if (find_f(a[0], a[1], a[2], 2 * k - 3) > 0.001)
		{
			vector_n(d, find_f(a[0], a[1], a[2], 2 * k - 3), vec);
			vector_plus(vec, dot, vec);
			vector_minus(vec, mlx->data.cr->cc, vec);
			if (inner_product(vec, mlx->data.cr->nc) < mlx->data.cr->h)
			{
				if (inner_product(vec, mlx->data.cr->nc) > 0)
					return (1);
			}
		}
		k--;
	}
	return (0);
}

int	check_hit_gray_cr_d(double *d, double *dot, t_mlx *mlx)
{
	if (check_hit_gray_cr_bot_d(d, dot, mlx) == 1)
		return (1);
	if (check_hit_gray_cr_side_d(d, dot, mlx) == 1)
		return (1);
	return (0);
}

int	check_hit_gray_cr(t_mlx *mlx, int i, int j)
{
	t_cron	*save;
	double	light[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	save = mlx->data.cr;
	while (mlx->data.cr != NULL)
	{
		if (check_hit_gray_cr_d(light, mlx->ray[i][j].dot, mlx) == 1)
		{
			mlx->data.cr = save;
			return (1);
		}
		mlx->data.cr = mlx->data.cr->next;
	}
	mlx->data.cr = save;
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
	else if (check_hit_gray_cr(mlx, i, j) == 1)
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
	mlx->img.data[1600 * j + i] = apply_color(mlx->ray[i][j].sum_rgb);
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
	while (i < 1600)
	{
		j = 0;
		while (j < 900)
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
		test(mlx->data);
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