/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:07:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/02 17:15:21 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	close_none_data(t_mlx *mlx)
{
	if (mlx->data.num.count_al == 0)
	{
		free(mlx->data.al);
		mlx->data.al = NULL;
	}
	if (mlx->data.num.count_l == 0)
	{
		free(mlx->data.l);
		mlx->data.l = NULL;
	}
	if (mlx->data.num.count_cam != 1)
		print_error("should be at least one camera.");
	if (mlx->data.num.count_al > 1)
		print_error("should be one alight.");
}

static void	close_none_object(t_mlx *mlx)
{
	if (mlx->data.num.count_sp == 0)
	{
		free(mlx->data.sp);
		mlx->data.sp = NULL;
	}
	if (mlx->data.num.count_pl == 0)
	{
		free(mlx->data.pl);
		mlx->data.pl = NULL;
	}
	if (mlx->data.num.count_cn == 0)
	{
		free(mlx->data.cn);
		mlx->data.cn = NULL;
	}
	if (mlx->data.num.count_cy == 0)
	{
		free(mlx->data.cy);
		mlx->data.cy = NULL;
	}
}

static void	check_obj(char *str, t_mlx *mlx)
{
	if (div_str(str, "A") == 1)
		push_a(str, mlx);
	else if (div_str(str, "C") == 1)
		push_c(str, mlx);
	else if (div_str(str, "L") == 1)
		push_l(str, mlx);
	else if (div_str(str, "sp") == 1)
		push_sp(str, mlx);
	else if (div_str(str, "pl") == 1)
		push_pl(str, mlx);
	else if (div_str(str, "cy") == 1)
		push_cy(str, mlx);
	else if (div_str(str, "cn") == 1)
		push_cn(str, mlx);
	else if (*str != '\0')
		print_error("invalid object name.");
}

static void	push_data(int fd, t_mlx *mlx)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (!(*str == '\n' && ft_strlen(str) == 1))
			check_obj(str, mlx);
		free(str);
		str = get_next_line(fd);
	}
}

void	check_input(char *argv, t_mlx *mlx)
{
	check_format(argv, ".rt");
	push_data(open_data(argv), mlx);
	close_none_data(mlx);
	close_none_object(mlx);
}
