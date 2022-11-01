/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:29:38 by chanhyle          #+#    #+#             */
/*   Updated: 2022/11/01 13:31:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	count_split(char **file_name)
{
	int	cnt;

	cnt = 0;
	while (file_name[cnt])
		cnt++;
	return (cnt);
}

static void	free_split(char **file_name, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
		free(file_name[i++]);
	free(file_name);
}

static void	remove_newline(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 1] == '\n')
		file_name[i - 1] = '\0';
}

static void	open_xpm_file(t_img *img, char *file_name, t_mlx *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx->mlx, file_name, \
										&(img->w), &(img->h));
	if (img->img == NULL)
		print_error("couldn't open xpm file.");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
											&img->size_l, &img->endian);
}

t_texture	push_xpm(t_xpm *xpm, char **str, t_mlx *mlx)
{
	char	**file_name;
	int		file_count;

	file_name = ft_split(*str, ' ');
	if (file_name == NULL)
		print_error("malloc error.");
	file_count = count_split(file_name);
	if (file_count != 3)
		print_error("need both image and normal xpm files only.");
	remove_newline(file_name[2]);
	check_format(file_name[1], ".xpm");
	check_format(file_name[2], ".xpm");
	open_xpm_file(&(xpm->img), file_name[1], mlx);
	open_xpm_file(&(xpm->normal), file_name[2], mlx);
	while (**str != '\n' && **str != '\0')
		(*str)++;
	free_split(file_name, file_count);
	return (BUMP);
}
