/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_data1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:16:18 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/07 20:48:08 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_texture	push_rgb(unsigned char *rgb, char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (div_str(*str, "checker") == 1)
	{
		*str += 7;
		return (CHECKER);
	}
	while (i < 3)
	{
		rgb[i] = check_range(ft_char_double(*str, &count), 0, 255, \
						"invalid range of rgb data.");
		*str += count;
		if (**str != ',' && i != 2)
			print_error("invalid rgb data.");
		if (i != 2)
			(*str)++;
		i++;
	}
	return (NONE);
}

void	push_x_y_z(double *data, char **str)
{
	int	i;
	int	count;

	i = 0;
	while (i < 3)
	{
		count = 0;
		data[i] = ft_char_double(*str, &count);
		*str += count;
		if (**str != ',' && i != 2)
			print_error("invalid vector data.");
		if (i != 2)
			(*str)++;
		i++;
	}
}

void	push_normal_x_y_z(double *data, char **str)
{
	int	i;
	int	count;

	i = 0;
	while (i < 3)
	{
		count = 0;
		data[i] = check_range(ft_char_double(*str, &count), -1, 1, \
						"invalid range of normal vector data.");
		*str += count;
		if (**str != ',' && i != 2)
			print_error("invalid normal vector data.");
		if (i != 2)
			(*str)++;
		i++;
	}
}
