/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_vector1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:43:46 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 20:46:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	inner_product(double *u, double *w)
{
	return (u[0] * w[0] + u[1] * w[1] + u[2] * w[2]);
}

void	cross_product(double *u, double *w, double *result)
{
	result[0] = u[1] * w[2] - u[2] * w[1];
	result[1] = u[2] * w[0] - u[0] * w[2];
	result[2] = u[0] * w[1] - u[1] * w[0];
}

double	vector_size(double *x)
{
	return (sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]));
}

void	normalize_vector(double *vec)
{
	double	size;

	size = vector_size(vec);
	vec[0] /= size;
	vec[1] /= size;
	vec[2] /= size;
}

void	vector_copy(double *x, double *copy)
{
	x[0] = copy[0];
	x[1] = copy[1];
	x[2] = copy[2];
}
