/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:16:16 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/02 17:10:49 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_light	*create_new_light(int obj_cnt, t_light *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_light *)malloc(sizeof(t_light) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_l(char *str, t_mlx *mlx)
{
	int		count;
	t_light	*save;

	if (mlx->data.num.count_l > 1)
		print_error("too much light.");
	save = mlx->data.l;
	str++;
	mlx->data.l = create_new_light(mlx->data.num.count_l, mlx->data.l);
	count = 0;
	mlx->data.num.count_l += 1;
	push_x_y_z(&(mlx->data.l->x[0]), &str);
	mlx->data.l->ratio = check_range(ft_char_double(str, &count), 0, 1, \
							"invalid range of light ratio data.");
	str += count;
	push_rgb(&(mlx->data.l->rgb[0]), &str);
	null_check(str);
	mlx->data.l = save;
}

static t_sphere	*create_new_sphere(int obj_cnt, t_sphere *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_sphere *)malloc(sizeof(t_sphere) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_sp(char *str, t_mlx *mlx)
{
	int			count;
	t_sphere	*save;

	save = mlx->data.sp;
	count = 0;
	str += 2;
	mlx->data.sp = create_new_sphere(mlx->data.num.count_sp, mlx->data.sp);
	mlx->data.num.count_sp += 1;
	push_x_y_z(&(mlx->data.sp->c[0]), &str);
	mlx->data.sp->r = check_range(ft_char_double(str, &count), 0, DBL_MAX, \
						"invalid range of sphere radius data.");
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.sp->mode = push_xpm(&(mlx->data.sp->xpm), &str, mlx);
	else
		mlx->data.sp->mode = push_rgb(&(mlx->data.sp->rgb[0]), &str);
	null_check(str);
	mlx->data.sp = save;
}
