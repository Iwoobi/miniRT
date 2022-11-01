/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:53:01 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 13:47:56 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_alight	*create_new_alight(int obj_cnt, t_alight *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_alight *)malloc(sizeof(t_alight) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_a(char *str, t_mlx *mlx)
{
	int			count;
	t_alight	*save;

	if (mlx->data.num.count_al > 0)
		print_error("too much ambient.");
	save = mlx->data.al;
	str++;
	mlx->data.al = create_new_alight(mlx->data.num.count_al, mlx->data.al);
	count = 0;
	mlx->data.num.count_al += 1;
	mlx->data.al->ratio = check_range(ft_char_double(str, &count), 0, 1, \
							"invalid range of ambient ratio data.");
	str += count;
	push_rgb(&(mlx->data.al->rgb[0]), &str);
	null_check(str);
	mlx->data.al = save;
}

static t_cam	*create_new_camera(int obj_cnt, t_cam *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_cam *)malloc(sizeof(t_cam) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_c(char *str, t_mlx *mlx)
{
	int		count;
	t_cam	*save;

	if (mlx->data.num.count_cam > 0)
		print_error("too much camera.");
	save = mlx->data.cam;
	str++;
	mlx->data.cam = create_new_camera(mlx->data.num.count_cam, mlx->data.cam);
	count = 0;
	mlx->data.num.count_cam += 1;
	push_x_y_z(&(mlx->data.cam->x[0]), &str);
	push_normal_x_y_z(&(mlx->data.cam->n[0]), &str);
	mlx->data.cam->fov = check_range(ft_char_double(str, &count), 0, 180, \
							"invalid camera fov data.");
	str += count;
	null_check(str);
	mlx->data.cam = save;
}
