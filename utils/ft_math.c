/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:25:18 by youhan            #+#    #+#             */
/*   Updated: 2022/11/03 14:58:32 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}
