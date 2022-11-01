/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:11:54 by youhan            #+#    #+#             */
/*   Updated: 2022/11/01 20:53:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	press_key(int key_code)
{
	if (key_code == KEY_ESC)
		exit(0);
	return (1);
}

void	ft_mlx_init(t_mlx *my_mlx)
{
	my_mlx->mlx = mlx_init();
	if (my_mlx->mlx == NULL)
		exit(1);
	my_mlx->win = mlx_new_window(my_mlx->mlx, my_mlx->size[0], \
							my_mlx->size[1], "miniRT");
	if (my_mlx->win == NULL)
		exit(1);
	my_mlx->img.img = mlx_new_image(my_mlx->mlx, my_mlx->size[0], \
							my_mlx->size[1]);
	if (my_mlx->img.img == NULL)
		exit(1);
	my_mlx->img.data = (int *)mlx_get_data_addr(my_mlx->img.img,
			&my_mlx->img.bpp, &my_mlx->img.size_l, &my_mlx->img.endian);
	if (my_mlx->img.data == NULL)
		exit(1);
}
