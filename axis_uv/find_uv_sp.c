/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_uv_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:53:20 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 22:00:49 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	uv_axis_sp(double *d, t_mlx *mlx)
{
	double	x[3];
	double	size;

	x[0] = mlx->t * d[0] - mlx->data.sp->cc[0];
	x[1] = mlx->t * d[1] - mlx->data.sp->cc[1];
	x[2] = mlx->t * d[2] - mlx->data.sp->cc[2];
	size = vector_size(x);
	x[0] /= size;
	x[1] /= size;
	x[2] /= size;
	mlx->data.sp->u[0] = (atan2(-1 * x[2], x[0]) + M_PI) / (2 * M_PI);
	mlx->data.sp->u[1] = acos(-1 * x[1]) / (M_PI);
	mlx->data.sp->checker_u[0] = 8 * mlx->data.sp->r * mlx->data.sp->u[0];
	mlx->data.sp->checker_u[1] = 4 * mlx->data.sp->r * mlx->data.sp->u[1];
}
