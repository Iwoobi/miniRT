/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:02:14 by youhan            #+#    #+#             */
/*   Updated: 2022/11/02 17:08:33 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	while (tmp[i] != '\0' && tmp[i] != ' ')
	{
		s[i] = tmp[i];
		i++;
	}
	s[i] = '\0';
}

void	ft_strcopy2(char *s, char *tmp)
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (0);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)ptr)[i++] = 0;
		return (ptr);
	}
}
