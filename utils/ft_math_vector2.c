/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_vector2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:45:22 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 20:58:00 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	vector_n(double *x, double val, double *result)
{
	result[0] = x[0] * val;
	result[1] = x[1] * val;
	result[2] = x[2] * val;
}

void	vector_plus(double *x, double *y, double *result)
{
	result[0] = x[0] + y[0];
	result[1] = x[1] + y[1];
	result[2] = x[2] + y[2];
}

void	vector_minus(double *x, double *y, double *result)
{
	result[0] = x[0] - y[0];
	result[1] = x[1] - y[1];
	result[2] = x[2] - y[2];
}

void	hex_to_rgb(int hex, unsigned int *rgb)
{
	rgb[2] = hex % 256;
	hex /= 256;
	rgb[1] = hex % 256;
	hex /= 256;
	rgb[0] = hex;
}

void	hex_to_rgb_double(int hex, double *rgb)
{
	rgb[2] = hex % 256;
	hex /= 256;
	rgb[1] = hex % 256;
	hex /= 256;
	rgb[0] = hex;
}
