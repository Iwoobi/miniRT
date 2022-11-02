/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:15:04 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:30:01 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	trans_rot_data(double x[3], t_mdata m)
{
	double	save[3];

	save[0] = x[0];
	save[1] = x[1];
	save[2] = x[2];
	x[0] = m.rot[0] * save[0] + m.rot[1] * save[1] + m.rot[2] * save[2];
	x[1] = m.rot[3] * save[0] + m.rot[4] * save[1] + m.rot[5] * save[2];
	x[2] = m.rot[6] * save[0] + m.rot[7] * save[1] + m.rot[8] * save[2];
}

int	rot_data_check(t_cam cam)
{
	if (cam.n[0] == 0)
	{
		if (cam.n[1] == 0)
		{
			if (cam.n[2] != 0)
				return (-1);
			print_error("invalid camera rotate.");
		}
	}
	return (0);
}
