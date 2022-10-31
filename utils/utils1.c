/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:35:46 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 00:54:35 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	check_format(char *argv, char *format)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	j = 0;
	cnt = 0;
	while (argv[i])
		i++;
	while (format[j])
		j++;
	i--;
	j--;
	while (cnt <= j)
	{
		if (argv[i] != format[j - cnt])
			print_error("invalid file format.");
		i--;
		cnt++;
	}
}

int	open_data(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		print_error("invalid file name.");
	return (fd);
}

int	div_str(char *str, char *div)
{
	if (*str == '\0')
		return (-1);
	if (str == NULL || div == NULL)
		return (-1);
	while (*div != '\0')
	{
		if (*div != *str)
			return (-1);
		div++;
		str++;
	}
	if (*str == ' ' || *str == '\n' || *str == '\0')
		return (1);
	return (-1);
}

void	print_error(char *str)
{
	write(STDERR_FILENO, "Error\n", ft_strlen("Error\n"));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

double	check_range(double res, double min, double max, char *msg)
{
	if (min > res || max < res)
		print_error(msg);
	return (res);
}
