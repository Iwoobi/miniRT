/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:37:56 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 13:50:05 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_cone	*create_new_cone(int obj_cnt, t_cone *obj_ptr)
{
	int	count;

	count = 0;
	while (obj_cnt > count)
	{
		if (obj_cnt - count == 1)
		{
			obj_ptr->next = (t_cone *)malloc(sizeof(t_cone) * 1);
			if (obj_ptr->next == NULL)
				print_error("malloc error.");
			obj_ptr->next->next = NULL;
		}
		obj_ptr = obj_ptr->next;
		count++;
	}
	return (obj_ptr);
}

void	push_cn(char *str, t_mlx *mlx)
{
	int		count;
	t_cone	*save;

	save = mlx->data.cn;
	str += 2;
	mlx->data.cn = create_new_cone(mlx->data.num.count_cn, mlx->data.cn);
	count = 0;
	mlx->data.num.count_cn += 1;
	push_x_y_z(&(mlx->data.cn->c[0]), &str);
	push_normal_x_y_z(&(mlx->data.cn->n[0]), &str);
	mlx->data.cn->r = check_range(ft_char_double(str, &count), 0, DBL_MAX, \
							"invalid range of cone radius data.");
	str += count;
	count = 0;
	mlx->data.cn->h = check_range(ft_char_double(str, &count), 0, DBL_MAX, \
							"invalid range of cone height data.");
	str += count;
	if (check_bump_word(str) == 1)
		mlx->data.cn->mode = push_xpm(&(mlx->data.cn->xpm), &str, mlx);
	else
		mlx->data.cn->mode = push_rgb(&(mlx->data.cn->rgb[0]), &str);
	null_check(str);
	mlx->data.cn = save;
}
