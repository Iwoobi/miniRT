/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:26:30 by youhan            #+#    #+#             */
/*   Updated: 2022/10/31 23:56:40 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	ft_back_num(char **str, double *n)
{
	int	back_n;
	int	count;

	count = 0;
	back_n = 0;
	(*str)++;
	if (!(**str >= '0' && **str <= '9'))
		print_error("no number after dot.");
	while (**str >= '0' && **str <= '9')
	{
		back_n = back_n * 10 + **str - '0';
		(*str)++;
		count++;
	}
	*n += back_n / (pow(10, count));
}

double	ft_char_double(char *str, int *count)
{
	int			sign;
	char		*save;
	double		n;

	save = str;
	sign = 1;
	n = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	if (*str == '.')
		ft_back_num(&str, &n);
	*count = str - save;
	return (n * sign);
}
