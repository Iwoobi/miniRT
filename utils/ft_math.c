/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:25:18 by youhan            #+#    #+#             */
/*   Updated: 2022/11/01 20:51:51 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	ft_radian(int a)
{
	return ((double)(a * M_PI) / 180);
}

double	pow_2(double a)
{
	return (a * a);
}

double	equation_d(double a, double b, double c)
{
	return (pow_2(b) - 4 * (a * c));
}

double	find_f(double a, double b, double c, double flag)
{
	if (flag > 0)
		return ((-b - sqrt(equation_d(a, b, c))) / (2 * a));
	else
		return ((-b + sqrt(equation_d(a, b, c))) / (2 * a));
}
