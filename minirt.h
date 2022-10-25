/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:06:43 by youhan            #+#    #+#             */
/*   Updated: 2022/10/25 22:24:30 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# define PRESS 2
# define CLOSED 17

# include <stdio.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include "./mlx/mlx.h"

typedef enum e_obj
{
	PL,
	CY,
	SP
}	t_obj;

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
/*데이터*/

typedef struct s_plane
{
	double			x[3];
	double			n[3];
	double			xc[3];
	double			nc[3];
	double			u[2];
	int				checker;
	unsigned char	rgb[3];
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	double			c[3];
	double			cc[3];
	double			u[2];
	double			r;
	int				checker;
	unsigned char	rgb[3];
	struct s_sphere	*next;
}	t_sphere;


typedef struct s_cylinder
{
	double				c[3];
	double				cc[3];
	double				h;
	double				r;
	double				u[2];
	double				n[3];
	double				nc[3];
	int					checker;
	unsigned char		rgb[3];
	struct s_cylinder	*next;
}	t_cylinder;

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


typedef struct s_data
{
	t_light		*l;
	t_alight	*al;
	t_cam		*cam;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	int			count_l;
	int			count_al;
	int			count_cam;
	int			count_sp;
	int			count_pl;
	int			count_cy;
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
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	xpm;
	t_ray	**ray;
	t_data	data;
	int		size[2];
	int		cam_num;
	double	t;
	int		flag;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/*데이터*/
int	ft_strlen(char *str);
double	ft_char_double(char *str, int *count);

/*mlx*/
void	ft_mlx_init(t_mlx *my_mlx);

/*print*/
void	test_a(t_data mlx);
void	test_c(t_data mlx);
void	test_l(t_data mlx);
void	test_cy(t_data mlx);
void	test_sp(t_data mlx);
void	test_pl(t_data mlx);

void	ctest_l(t_data mlx);
void	ctest_cy(t_data mlx);
void	ctest_sp(t_data mlx);
void	ctest_pl(t_data mlx);

#endif