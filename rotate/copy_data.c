/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:07:53 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:10:34 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	copy_rot_l(t_mlx *mlx)
{
	t_light	*save;

	save = mlx->data.l;
	while (mlx->data.l != NULL)
	{
		mlx->data.l->xc[0] = mlx->data.l->x[0];
		mlx->data.l->xc[1] = mlx->data.l->x[1];
		mlx->data.l->xc[2] = mlx->data.l->x[2];
		mlx->data.l = mlx->data.l->next;
	}
	mlx->data.l = save;
}

void	copy_rot_sp(t_mlx *mlx)
{
	t_sphere	*save;

	save = mlx->data.sp;
	while (mlx->data.sp != NULL)
	{
		mlx->data.sp->cc[0] = mlx->data.sp->c[0];
		mlx->data.sp->cc[1] = mlx->data.sp->c[1];
		mlx->data.sp->cc[2] = mlx->data.sp->c[2];
		mlx->data.sp = mlx->data.sp->next;
	}
	mlx->data.sp = save;
}

void	copy_rot_pl(t_mlx *mlx)
{
	t_plane	*save;

	save = mlx->data.pl;
	while (mlx->data.pl != NULL)
	{
		mlx->data.pl->xc[0] = mlx->data.pl->x[0];
		mlx->data.pl->xc[1] = mlx->data.pl->x[1];
		mlx->data.pl->xc[2] = mlx->data.pl->x[2];
		mlx->data.pl->nc[0] = mlx->data.pl->n[0];
		mlx->data.pl->nc[1] = mlx->data.pl->n[1];
		mlx->data.pl->nc[2] = mlx->data.pl->n[2];
		mlx->data.pl = mlx->data.pl->next;
	}
	mlx->data.pl = save;
}

void	copy_rot_cy(t_mlx *mlx)
{
	t_cylinder	*save;

	save = mlx->data.cy;
	while (mlx->data.cy != NULL)
	{
		mlx->data.cy->cc[0] = mlx->data.cy->c[0];
		mlx->data.cy->cc[1] = mlx->data.cy->c[1];
		mlx->data.cy->cc[2] = mlx->data.cy->c[2];
		mlx->data.cy->nc[0] = mlx->data.cy->n[0];
		mlx->data.cy->nc[1] = mlx->data.cy->n[1];
		mlx->data.cy->nc[2] = mlx->data.cy->n[2];
		mlx->data.cy = mlx->data.cy->next;
	}
	mlx->data.cy = save;
}

void	copy_rot_cn(t_mlx *mlx)
{
	t_cone	*save;

	save = mlx->data.cn;
	while (mlx->data.cn != NULL)
	{
		mlx->data.cn->cc[0] = mlx->data.cn->c[0];
		mlx->data.cn->cc[1] = mlx->data.cn->c[1];
		mlx->data.cn->cc[2] = mlx->data.cn->c[2];
		mlx->data.cn->nc[0] = mlx->data.cn->n[0];
		mlx->data.cn->nc[1] = mlx->data.cn->n[1];
		mlx->data.cn->nc[2] = mlx->data.cn->n[2];
		mlx->data.cn = mlx->data.cn->next;
	}
	mlx->data.cn = save;
}
