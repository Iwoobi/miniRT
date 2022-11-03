/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:06:43 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 16:45:44 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# define PRESS 				2
# define CLOSED 			17
# define EPSILON 			1e-10
# define WINDOW_WIDTH		1600
# define WINDOW_HEIGHT		900
# define KEY_ESC			53
# define PIXEL				1

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <float.h>
# include "get_next_line.h"
# include "./mlx/mlx.h"

typedef enum e_obj
{
	PL,
	CY,
	SP,
	CN
}	t_obj;

typedef enum e_texture
{
	NONE,
	CHECKER,
	BUMP
}	t_texture;

typedef struct s_cone_utils
{
	double	head[3];
	double	dot[3];
	double	a[3];
	double	val;
	int		i;
}	t_cone_utils;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_xpm
{
	t_img	img;
	t_img	normal;
}	t_xpm;
/*데이터*/

typedef struct s_plane
{
	double			x[3];
	double			n[3];
	double			xc[3];
	double			nc[3];
	double			u[2];
	double			checker_u[2];
	t_texture		mode;
	unsigned char	rgb[3];
	t_xpm			xpm;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	double			c[3];
	double			cc[3];
	double			u[2];
	double			checker_u[2];
	double			r;
	t_texture		mode;
	unsigned char	rgb[3];
	t_xpm			xpm;
	struct s_sphere	*next;
}	t_sphere;


typedef struct s_cylinder
{
	double				c[3];
	double				cc[3];
	double				h;
	double				r;
	double				u[2];
	double				checker_u[2];
	double				n[3];
	double				nc[3];
	t_texture			mode;
	unsigned char		rgb[3];
	t_xpm				xpm;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_cone
{
	double			c[3];
	double			cc[3];
	double			h;
	double			n[3];
	double			nc[3];
	double			r;
	double			u[2];
	double			checker_u[2];
	t_texture		mode;
	unsigned char	rgb[3];
	t_xpm			xpm;
	struct s_cone	*next;
}	t_cone;

typedef	struct s_alight
{
	double			ratio;
	unsigned char	rgb[3];
	struct s_alight	*next;
}	t_alight;

typedef	struct s_cam
{
	double			x[3];
	double			n[3];
	double			xc[3];
	double			nc[3];
	double			fov;
	struct s_cam	*next;
}	t_cam;

typedef struct s_light
{
	double			x[3];
	double			xc[3];
	double			ratio;
	unsigned char	rgb[3];
	struct s_light	*next;
}	t_light;

typedef struct s_count
{
	int	count_l;
	int	count_al;
	int	count_cam;
	int	count_sp;
	int	count_pl;
	int	count_cy;
	int	count_cn;
}	t_count;


typedef struct s_data
{
	t_light		*l;
	t_alight	*al;
	t_cam		*cam;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cone		*cn;
	t_count		num;
}	t_data;

typedef struct s_mdata
{
	double	rot[9];
	double	m[3];
}	t_mdata;

typedef struct s_ray
{
	double			n[3];
	double			deep;
	double			dot[3];
	double			d[3];
	unsigned int	rgb[3];
	unsigned int	sum_rgb[3];
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_ray	**ray;
	t_data	data;
	int		size[2];
	int		cam_num;
	double	t;
	int		flag;
}	t_mlx;


/*mlx*/
void	ft_mlx_init(t_mlx *my_mlx);
void	init_mlx_data(t_mlx *mlx);
int		press_key(int key_code);
int	ft_close(t_mlx *mlx);

/*pasring*/
char	**ft_split(char const *s, char c);
double	ft_char_double(char *str, int *count);
void	check_input(char *argv, t_mlx *mlx);
void	print_error(char *str);
void	push_a(char *str, t_mlx *mlx);
void	push_c(char *str, t_mlx *mlx);
void	push_l(char *str, t_mlx *mlx);
void	push_sp(char *str, t_mlx *mlx);
void	push_pl(char *str, t_mlx *mlx);
void	push_cy(char *str, t_mlx *mlx);
void	push_cn(char *str, t_mlx *mlx);
t_texture	push_rgb(unsigned char *rgb, char **str);
t_texture	push_xpm(t_xpm *xpm, char **str, t_mlx *mlx);
void	push_x_y_z(double *data, char **str);
void	push_normal_x_y_z(double *data, char **str);

/*utils*/
int		ft_strlen(char *str);
void	ft_strcopy(char *s, char *tmp);
void	ft_strcopy2(char *s, char *tmp);
int		ft_strlen_2(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	check_format(char *argv, char *format);
int	open_data(char *argv);
int	div_str(char *str, char *div);
void	print_error(char *str);
double	check_range(double res, double min, double max, char *msg);
void	null_check(char *str);
int		check_bump_word(char *str);
void	axis_x(double *result);
void	axis_y(double *result);
void	axis_z(double *result);

/*math*/
double	pow_2(double a);
double	deg_to_rad(double degree);
double	equation_d(double a, double b, double c);
double	find_f(double a, double b, double c, double flag);

double	inner_product(double *u, double *w);
void	cross_product(double *u, double *w, double *result);
double	vector_size(double *x);
void	normalize_vector(double *vec);
void	vector_copy(double *x, double *copy);
void	vector_n(double *x, double val, double *result);
void	vector_plus(double *x, double *y, double *result);
void	vector_minus(double *x, double *y, double *result);
void	hex_to_rgb(int hex, unsigned int *rgb);
void	hex_to_rgb_double(int hex, double *rgb);

/*rotate*/

void	copy_rot_l(t_mlx *mlx);
void	copy_rot_sp(t_mlx *mlx);
void	copy_rot_pl(t_mlx *mlx);
void	copy_rot_cy(t_mlx *mlx);
void	copy_rot_cn(t_mlx *mlx);
void	updata_rot_l(t_data *data, t_mdata mdata);
void	updata_rot_sp(t_data *data, t_mdata mdata);
void	updata_rot_pl(t_data *data, t_mdata mdata);
void	updata_rot_cy(t_data *data, t_mdata mdata);
void	updata_rot_cn(t_data *data, t_mdata mdata);
t_mdata	data_cam_num_init(t_mlx mlx);
void	trans_rot_data(double x[3], t_mdata mdata);
int		rot_data_check(t_cam cam);
void	exec_rot_data(t_mlx *mlx, t_mdata mdata);
void	copy_rot_data(t_mlx *mlx);



/*uv*/
void	uv_axis_sp(double *d, t_mlx *mlx);
void	uv_axis_cn(t_mlx *mlx, double *d);
void	uv_axis_cy(t_mlx *mlx, double *d);
void	uv_axis_pl(double *d, t_mlx *mlx);
void	normal_vector_bump(t_mlx *mlx, int i, int j, t_obj obj);

/*hit*/

void	check_hit_cy(t_mlx *mlx, double *d, int i, int j);
int		check_hit_cy_d(double *d, double *n, double *c, t_mlx *mlx);
void	check_hit_cn(t_mlx *mlx, double *d, int i, int j);
void	find_cone_head(double *n, double h, double *c, double *result);
int		check_hit_cn_d(double *d, double *n, double *c, t_mlx *mlx);
void	check_hit_sp(t_mlx *mlx, double *d, int i, int j);
void	check_hit_pl(t_mlx *mlx, double *d, int i, int j);
void	color_select(t_mlx *mlx, unsigned int *rgb, t_obj obj);
void	canvas_match(t_mlx *mlx);

/*ray_tracer*/
void	phong_init(t_mlx *mlx);
void	phong_reset(unsigned int phong[3][3]);
void	reset_phong_light(unsigned int phong[3][3]);
int	apply_color(unsigned int *rgb);
void	ambient_light(t_mlx *mlx, int i, int j, unsigned int *amb);
void	diffuse_light(t_mlx *mlx, int i, int j, unsigned int *diff);
void	specular_light(t_mlx *mlx, int i, int j, unsigned int *spec);
int	check_hit_gray_sp(t_mlx *mlx, int i, int j);
int	check_hit_gray_pl(t_mlx *mlx, int i, int j);
int	check_hit_gray_cy(t_mlx *mlx, int i, int j);
int	check_hit_gray_cn(t_mlx *mlx, int i, int j);

/*print*/
void	test(t_data mlx);
void	test_a(t_data mlx);
void	test_c(t_data mlx);
void	test_l(t_data mlx);
void	test_cy(t_data mlx);
void	test_sp(t_data mlx);
void	test_pl(t_data mlx);
void	test_cn(t_data mlx);

void	ctest(t_data mlx);
void	ctest_l(t_data mlx);
void	ctest_cy(t_data mlx);
void	ctest_sp(t_data mlx);
void	ctest_pl(t_data mlx);
void	ctest_cn(t_data mlx);

void	print_rot_data(t_mdata data);

#endif