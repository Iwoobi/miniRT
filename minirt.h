/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:06:43 by youhan            #+#    #+#             */
/*   Updated: 2022/11/01 01:17:46 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# define PRESS 2
# define CLOSED 17
# define EPSILON 1e-300
# define WINDOW_WIDTH	1600
# define WINDOW_HEIGHT	900
# define KEY_ESC		53

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

/*데이터*/
int		ft_strlen(char *str);
void	ft_strcopy(char *s, char *tmp);
void	ft_strcopy2(char *s, char *tmp);
int		ft_strlen_2(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
/*mlx*/
void	ft_mlx_init(t_mlx *my_mlx);

/*pasring*/
char	**ft_split(char const *s, char c);
double	ft_char_double(char *str, int *count);
void	check_input(char *argv, t_mlx *mlx);
int		check_bump_word(char *str);
void	print_error(char *str);
void	push_a(char *str, t_mlx *mlx);
void	push_c(char *str, t_mlx *mlx);
void	push_l(char *str, t_mlx *mlx);
void	push_sp(char *str, t_mlx *mlx);
void	push_pl(char *str, t_mlx *mlx);
void	push_cy(char *str, t_mlx *mlx);
void	push_cn(char *str, t_mlx *mlx);
t_texture	push_rgb(unsigned char *rgb, char **str);

/*utils*/
void	check_format(char *argv, char *format);
int	open_data(char *argv);
int	div_str(char *str, char *div);
void	print_error(char *str);
double	check_range(double res, double min, double max, char *msg);
void	null_check(char *str);

/*print*/
void	test_a(t_data mlx);
void	test_c(t_data mlx);
void	test_l(t_data mlx);
void	test_cy(t_data mlx);
void	test_sp(t_data mlx);
void	test_pl(t_data mlx);
void	test_cn(t_data mlx);


void	ctest_l(t_data mlx);
void	ctest_cy(t_data mlx);
void	ctest_sp(t_data mlx);
void	ctest_pl(t_data mlx);
void	ctest_cn(t_data mlx);
#endif