/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:02:14 by youhan            #+#    #+#             */
/*   Updated: 2022/10/26 01:00:14 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_2(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

void	ft_strcopy(char *s, char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
	{
		s[i] = tmp[i];
		i++;
	}
	s[i] = '\0';
}