/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:18:31 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:30:01 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	updata_rot(t_mlx *mlx, t_mdata mdata)
{
	updata_rot_l(&(mlx->data), mdata);
	updata_rot_sp(&(mlx->data), mdata);
	updata_rot_pl(&(mlx->data), mdata);
	updata_rot_cy(&(mlx->data), mdata);
	updata_rot_cn(&(mlx->data), mdata);
}

void	copy_rot_data(t_mlx *mlx)
{
	copy_rot_l(mlx);
	copy_rot_sp(mlx);
	copy_rot_pl(mlx);
	copy_rot_cy(mlx);
	copy_rot_cn(mlx);
}

void	exec_rot_data(t_mlx *mlx, t_mdata mdata)
{
	updata_rot(mlx, mdata);
}
