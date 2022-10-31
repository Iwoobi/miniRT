/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:53:01 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 01:17:29 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	create_new_object(int obj_cnt, t_alight *obj_ptr)
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
}

void	push_a(char *str, t_mlx *mlx)
{
	int			count;
	t_alight	*save;

	if (mlx->data.num.count_al > 0)
		print_error("too much ambient.");
	save = mlx->data.al;
	str++;
	create_new_object(mlx->data.num.count_al, mlx->data.al);
	count = 0;
	mlx->data.num.count_al += 1;
	mlx->data.al->ratio = check_range(ft_char_double(str, &count), 0, 1, \
							"invalid range of ambient ratio data.");
	str += count;
	push_rgb(&(mlx->data.al->rgb[0]), &str);
	null_check(str);
	mlx->data.al = save;
}