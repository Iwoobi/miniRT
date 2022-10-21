/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:52:24 by youhan            #+#    #+#             */
/*   Updated: 2022/09/07 18:52:27 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_move_str(char **str, int a)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(&((*str)[a])) + 1);
	if (!tmp)
		return (-1);
	while ((*str)[a + i] != '\0')
	{
		tmp[i] = (*str)[a + i];
		i++;
	}
	tmp[i] = '\0';
	free((*str));
	(*str) = malloc(sizeof(char) * i + 1);
	if (!(*str))
		return (-1);
	ft_join(str, tmp, 2);
	free(tmp);
	return (1);
}

char	*ft_str_return_fin(char **str, int *i, int *j)
{
	char	*tmp;

	*j = *i;
	tmp = malloc(sizeof(char) * (*i + 1) + 1);
	if (!tmp)
		return (NULL);
	tmp[*i + 1] = '\0';
	while (*i >= 0)
	{
		tmp[*i] = (*str)[*i];
		*i = *i - 1;
	}
	if ((*str)[*j + 1] == '\0')
	{
		free(*str);
		*str = NULL;
		return (tmp);
	}
	if (ft_move_str(str, *j + 1) == -1)
		return (NULL);
	return (tmp);
}

char	*ft_str_return(char **str, int *k)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	*k = -1;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\n')
			return (ft_str_return_fin(str, &i, &j));
		i++;
	}
	*k = 0;
	if (k[1] == 0)
	{
		tmp = malloc(sizeof(char) * ft_strlen(*str) + 1);
		ft_join(&tmp, *str, 0);
		free(*str);
		*str = NULL;
		*k = 2;
		return (tmp);
	}
	return (NULL);
}

int	ft_read(int fd, char **str, char *buff, int size)
{
	int		i;
	char	*tmp;

	i = read(fd, buff, size);
	if (i <= 0)
		return (0);
	buff[i] = '\0';
	tmp = malloc(sizeof(char) * ft_strlen(*str) + 1);
	if (!tmp)
		return (-2);
	ft_join(&tmp, *str, 4);
	if (*str != NULL)
		free(*str);
	*str = malloc(sizeof(char) * i + ft_strlen(tmp) + 1);
	if (*str == NULL)
		return (-2);
	ft_join(str, tmp, 5);
	ft_join(str, buff, 1);
	free(tmp);
	return (i);
}

char	*get_next_line(int fd)
{
	char		buff[5];
	static char	*str_backup;
	char		*str_return;
	int			i[3];

	i[0] = 3;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (i[0] == 0 || i[0] == 3)
			i[1] = ft_read(fd, &str_backup, buff, 4);
		if (i[1] == -2 || i[0] == -1)
			return (NULL);
		if (i[1] == 0 && str_backup == NULL)
			return (NULL);
		str_return = ft_str_return(&str_backup, &i[0]);
		if (str_return != NULL)
			return (str_return);
	}
}
