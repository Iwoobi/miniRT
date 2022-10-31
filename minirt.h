/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:06:43 by youhan            #+#    #+#             */
/*   Updated: 2022/10/31 21:03:11 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# define PRESS 2
# define CLOSED 17
# define EPSILON 1e-300

# include <stdio.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <float.h>
# include "./mlx/mlx.h"

typedef enum e_obj
{
	PL,
	CY,
	SP,
	CR
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

typedef struct s_cron
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
	struct s_cron	*next;
}	t_cron;

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
	int	count_cr;
}	t_count;


typedef struct s_data
{
	t_light		*l;
	t_alight	*al;
	t_cam		*cam;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cron		*cr;
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
double	ft_char_double(char *str, int *count);
int		ft_strlen_2(char *str);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
/*mlx*/
void	ft_mlx_init(t_mlx *my_mlx);

/*pasring*/
int	check_bump_word(char *str);

/*print*/
void	test_a(t_data mlx);
void	test_c(t_data mlx);
void	test_l(t_data mlx);
void	test_cy(t_data mlx);
void	test_sp(t_data mlx);
void	test_pl(t_data mlx);
void	test_cr(t_data mlx);


void	ctest_l(t_data mlx);
void	ctest_cy(t_data mlx);
void	ctest_sp(t_data mlx);
void	ctest_pl(t_data mlx);
void	ctest_cr(t_data mlx);
#endif