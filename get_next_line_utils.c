/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:52:18 by youhan            #+#    #+#             */
/*   Updated: 2022/09/07 18:52:20 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_join(char **str, char *back, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (back == NULL)
	{
		(*str)[0] = '\0';
		return ;
	}	
	if (flag == 1)
	{
		while ((*str)[i] != '\0')
			i++;
	}
	while (back[j] != '\0')
	{
		(*str)[i + j] = back[j];
		j++;
	}
	(*str)[i + j] = '\0';
}
