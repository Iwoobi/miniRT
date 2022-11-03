/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:00:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/03 16:10:21 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	phong_reset(unsigned int phong[3][3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			phong[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	reset_phong_light(unsigned int phong[3][3])
{
	phong[1][0] = 0;
	phong[1][1] = 0;
	phong[1][2] = 0;
	phong[2][0] = 0;
	phong[2][1] = 0;
	phong[2][2] = 0;
}

int	apply_color(unsigned int *rgb)
{
	return (pow_2(256) * rgb[0] + 256 * rgb[1] + rgb[2]);
}
