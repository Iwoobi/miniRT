/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updata_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:10:14 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 21:30:01 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	updata_rot_l(t_data *data, t_mdata mdata)
{
	t_light	*save;

	save = data->l;
	while (data->l != NULL)
	{
		data->l->xc[0] -= mdata.m[0];
		data->l->xc[1] -= mdata.m[1];
		data->l->xc[2] -= mdata.m[2];
		trans_rot_data(data->l->xc, mdata);
		data->l = data->l->next;
	}
	data->l = save;
}

void	updata_rot_sp(t_data *data, t_mdata mdata)
{
	t_sphere	*save;

	save = data->sp;
	while (data->sp != NULL)
	{
		data->sp->cc[0] -= mdata.m[0];
		data->sp->cc[1] -= mdata.m[1];
		data->sp->cc[2] -= mdata.m[2];
		trans_rot_data(data->sp->cc, mdata);
		data->sp = data->sp->next;
	}
	data->sp = save;
}

void	updata_rot_pl(t_data *data, t_mdata mdata)
{
	t_plane	*save;

	save = data->pl;
	while (data->pl != NULL)
	{
		data->pl->xc[0] -= mdata.m[0];
		data->pl->xc[1] -= mdata.m[1];
		data->pl->xc[2] -= mdata.m[2];
		trans_rot_data(data->pl->xc, mdata);
		trans_rot_data(data->pl->nc, mdata);
		data->pl = data->pl->next;
	}
	data->pl = save;
}

void	updata_rot_cy(t_data *data, t_mdata mdata)
{
	t_cylinder	*save;

	save = data->cy;
	while (data->cy != NULL)
	{
		data->cy->cc[0] -= mdata.m[0];
		data->cy->cc[1] -= mdata.m[1];
		data->cy->cc[2] -= mdata.m[2];
		trans_rot_data(data->cy->cc, mdata);
		trans_rot_data(data->cy->nc, mdata);
		data->cy = data->cy->next;
	}
	data->cy = save;
}

void	updata_rot_cn(t_data *data, t_mdata mdata)
{
	t_cone	*save;

	save = data->cn;
	while (data->cn != NULL)
	{
		data->cn->cc[0] -= mdata.m[0];
		data->cn->cc[1] -= mdata.m[1];
		data->cn->cc[2] -= mdata.m[2];
		trans_rot_data(data->cn->cc, mdata);
		trans_rot_data(data->cn->nc, mdata);
		data->cn = data->cn->next;
	}
	data->cn = save;
}
