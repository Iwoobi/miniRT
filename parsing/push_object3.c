/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:32:39 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/05 14:38:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_plane	*create_new_plane(int obj_cnt, t_plane *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_plane *)malloc(sizeof(t_plane) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_pl(char *str, t_mlx *mlx)
{
	t_plane	*save;

	save = mlx->data.pl;
	str += 2;
	mlx->data.pl = create_new_plane(mlx->data.num.count_pl, mlx->data.pl);
	mlx->data.num.count_pl += 1;
	push_x_y_z(&(mlx->data.pl->x[0]), &str);
	push_normal_x_y_z(&(mlx->data.pl->n[0]), &str);
	if (check_bump_word(str) == 1)
		mlx->data.pl->mode = push_xpm(&(mlx->data.pl->xpm), &str, mlx);
	else
		mlx->data.pl->mode = push_rgb(&(mlx->data.pl->rgb[0]), &str);
	null_check(str);
	mlx->data.pl = save;
}

static t_cylinder	*create_new_cylinder(int obj_cnt, t_cylinder *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_cylinder *)malloc(sizeof(t_cylinder) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_cy(char *str, t_mlx *mlx)
{
	int			count;
	t_cylinder	*save;

	save = mlx->data.cy;
	str += 2;
	mlx->data.cy = create_new_cylinder(mlx->data.num.count_cy, mlx->data.cy);
	count = 0;
	mlx->data.num.count_cy += 1;
	push_x_y_z(&(mlx->data.cy->c[0]), &str);
	push_normal_x_y_z(&(mlx->data.cy->n[0]), &str);
	mlx->data.cy->r = check_range(ft_char_double(str, &count), 0, DBL_MAX, \
						"invalid range of cylinder radius data.");
	str += count;
	count = 0;
	mlx->data.cy->h = check_range(ft_char_double(str, &count), 0, DBL_MAX, \
						"invalid range of cylinder height data.");
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.cy->mode = push_xpm(&(mlx->data.cy->xpm), &str, mlx);
	else
		mlx->data.cy->mode = push_rgb(&(mlx->data.cy->rgb[0]), &str);
	null_check(str);
	mlx->data.cy = save;
}
