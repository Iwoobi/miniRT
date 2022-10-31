/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:16:18 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 01:20:23 by chanhyle         ###   ########.fr       */
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
		rgb[i] = check_range(ft_char_double(*str, &count), 0, 255, "invalid range of rgb data.");
		*str += count;
		if (**str != ',' && i != 2)
			print_error("invalid rgb data.");
		if (i != 2)
			(*str)++;
		i++;
	}
	return (NONE);
}