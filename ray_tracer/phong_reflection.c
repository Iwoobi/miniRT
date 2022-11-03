/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:55:39 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 16:08:33 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ambient_light(t_mlx *mlx, int i, int j, unsigned int *amb)
{
	amb[0] = mlx->data.al->rgb[0] * mlx->ray[i][j].rgb[0] \
		* mlx->data.al->ratio / 255;
	amb[1] = mlx->data.al->rgb[1] * mlx->ray[i][j].rgb[1] \
		* mlx->data.al->ratio / 255;
	amb[2] = mlx->data.al->rgb[2] * mlx->ray[i][j].rgb[2] \
		* mlx->data.al->ratio / 255;
}

void	diffuse_light(t_mlx *mlx, int i, int j, unsigned int *diff)
{
	double	light[3];
	double	res;

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	normalize_vector(light);
	normalize_vector(mlx->ray[i][j].n);
	res = inner_product(mlx->ray[i][j].n, light);
	if (res < EPSILON)
		res = 0;
	diff[0] = mlx->data.l->rgb[0] * mlx->ray[i][j].rgb[0] \
		* res * mlx->data.l->ratio / 255;
	diff[1] = mlx->data.l->rgb[1] * mlx->ray[i][j].rgb[1] \
		* res * mlx->data.l->ratio / 255;
	diff[2] = mlx->data.l->rgb[2] * mlx->ray[i][j].rgb[2] \
	* res * mlx->data.l->ratio / 255;
}

void	specular_light(t_mlx *mlx, int i, int j, unsigned int *spec)
{
	double	light[3];
	double	val;
	double	n[3];

	vector_minus(mlx->data.l->xc, mlx->ray[i][j].dot, light);
	val = inner_product(light, mlx->ray[i][j].n);
	vector_n(mlx->ray[i][j].n, 2 * val, n);
	vector_minus(n, light, light);
	normalize_vector(light);
	vector_n(mlx->ray[i][j].d, -1, n);
	val = inner_product(n, light);
	if (val < EPSILON)
		val = 0;
	val = pow(val, 10);
	spec[0] = 4 * mlx->data.l->rgb[0] * mlx->ray[i][j].rgb[0] \
		* mlx->data.al->ratio * val / 255;
	spec[1] = 4 * mlx->data.l->rgb[1] * mlx->ray[i][j].rgb[1] \
		* mlx->data.al->ratio * val / 255;
	spec[2] = 4 * mlx->data.l->rgb[2] * mlx->ray[i][j].rgb[2] \
		* mlx->data.al->ratio * val / 255;
}
