/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:04:02 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 15:09:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	color_val(unsigned int *rgb, unsigned char *obj_rgb)
{
	rgb[0] = obj_rgb[0];
	rgb[1] = obj_rgb[1];
	rgb[2] = obj_rgb[2];
}

static void	checker_board(double *uv, unsigned int *rgb)
{
	int	i;
	int	j;

	i = uv[0];
	j = uv[1];
	if ((i + j) % 2 != 0)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else
	{
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	}
}

static void	xpm_color_select(double *u, unsigned int *rgb, t_img img)
{
	int	i;
	int	j;

	i = u[0] * img.w;
	j = u[1] * img.h;
	hex_to_rgb(img.data[i + img.w * j], rgb);
}

void	color_select2(t_mlx *mlx, unsigned int *rgb, t_obj obj)
{
	if (obj == SP)
	{
		if (mlx->data.sp->mode == NONE)
			color_val(rgb, mlx->data.sp->rgb);
		else if (mlx->data.sp->mode == CHECKER)
			checker_board(mlx->data.sp->checker_u, rgb);
		else if (mlx->data.sp->mode == BUMP)
			xpm_color_select(mlx->data.sp->u, rgb, mlx->data.sp->xpm.img);
	}
	else if (obj == CN)
	{
		if (mlx->data.cn->mode == NONE)
			color_val(rgb, mlx->data.cn->rgb);
		else if (mlx->data.cn->mode == CHECKER)
			checker_board(mlx->data.cn->checker_u, rgb);
		else if (mlx->data.cn->mode == BUMP)
			xpm_color_select(mlx->data.cn->u, rgb, mlx->data.cn->xpm.img);
	}
}

void	color_select(t_mlx *mlx, unsigned int *rgb, t_obj obj)
{
	if (obj == PL)
	{
		if (mlx->data.pl->mode == NONE)
			color_val(rgb, mlx->data.pl->rgb);
		else if (mlx->data.pl->mode == CHECKER)
			checker_board(mlx->data.pl->checker_u, rgb);
		else if (mlx->data.pl->mode == BUMP)
			xpm_color_select(mlx->data.pl->u, rgb, mlx->data.pl->xpm.img);
	}
	else if (obj == CY)
	{
		if (mlx->data.cy->mode == NONE)
			color_val(rgb, mlx->data.cy->rgb);
		else if (mlx->data.cy->mode == CHECKER)
			checker_board(mlx->data.cy->checker_u, rgb);
		else if (mlx->data.cy->mode == BUMP)
			xpm_color_select(mlx->data.cy->u, rgb, mlx->data.cy->xpm.img);
	}
	else
		color_select2(mlx, rgb, obj);
}
