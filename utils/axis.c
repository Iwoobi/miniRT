/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:05:01 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:05:32 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	axis_x(double *result)
{
	result[0] = 1;
	result[1] = 0;
	result[2] = 0;
}

void	axis_y(double *result)
{
	result[0] = 0;
	result[1] = 1;
	result[2] = 0;
}

void	axis_z(double *result)
{
	result[0] = 0;
	result[1] = 0;
	result[2] = 1;
}