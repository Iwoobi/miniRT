/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:16:20 by youhan            #+#    #+#             */
/*   Updated: 2022/10/27 22:33:01 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_c(t_data mlx)
{
	int i;
	printf("\ntest cam\n");
	while (mlx.cam != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.cam->x[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.cam->n[i]);
			i++;
		}
		printf("FOV : %f\n", mlx.cam->fov);
		mlx.cam = mlx.cam->next;
	}
}


void	test_l(t_data mlx)
{
	int i;
	printf("\ntest light\n");
	while (mlx.l != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.l->x[i]);
			i++;
		}
		printf("ratio : %f\n", mlx.l->ratio);
		i = 0;
		while (i < 3)
		{
			printf("rgb[i] : %d\n",mlx.l->rgb[i]);
			i++;
		}
		mlx.l = mlx.l->next;
	}
}

void	test_a(t_data mlx)
{
	int i;
	
	printf("\ntest A\n");
	while (mlx.al != NULL)
	{
		printf("ratio : %f\n",mlx.al->ratio);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.al->rgb[i]);
			i++;
		}
		mlx.al = mlx.al->next;
	}
}

void	test_pl(t_data mlx)
{
	int i;
	
	printf("\ntest pl\n");
	while (mlx.pl != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.pl->x[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.pl->n[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.pl->rgb[i]);
			i++;
		}
		mlx.pl = mlx.pl->next;
	}
}

void	test_sp(t_data mlx)
{
	int i;
	
	printf("\ntest sp\n");
	while (mlx.sp != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("c[%d] : %f\n",i,mlx.sp->c[i]);
			i++;
		}
		printf("r : %f\n", mlx.sp->r);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.sp->rgb[i]);
			i++;
		}
		mlx.sp = mlx.sp->next;
	}
}

void	test_cy(t_data mlx)
{
	int i;
	
	printf("\ntest cy\n");
	while (mlx.cy != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.cy->c[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.cy->n[i]);
			i++;
		}
		printf("r : %f\n", mlx.cy->r);
		printf("h : %f\n", mlx.cy->h);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.cy->rgb[i]);
			i++;
		}
		mlx.cy = mlx.cy->next;
	}
}

void	test_cr(t_data mlx)
{
	int i;
	
	printf("\ntest cr\n");
	while (mlx.cr != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.cr->c[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.cr->n[i]);
			i++;
		}
		printf("r : %f\n", mlx.cr->r);
		printf("h : %f\n", mlx.cr->h);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.cr->rgb[i]);
			i++;
		}
		mlx.cr = mlx.cr->next;
	}
}


void	ctest_l(t_data mlx)
{
	int i;
	printf("\ntest light\n");
	while (mlx.l != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.l->xc[i]);
			i++;
		}
		printf("ratio : %f\n", mlx.l->ratio);
		i = 0;
		while (i < 3)
		{
			printf("rgb[i] : %d\n",mlx.l->rgb[i]);
			i++;
		}
		mlx.l = mlx.l->next;
	}
}

void	ctest_pl(t_data mlx)
{
	int i;
	
	printf("\ntest pl\n");
	while (mlx.pl != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.pl->xc[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.pl->nc[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.pl->rgb[i]);
			i++;
		}
		mlx.pl = mlx.pl->next;
	}
}

void	ctest_sp(t_data mlx)
{
	int i;
	
	printf("\ntest sp\n");
	while (mlx.sp != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("c[%d] : %f\n",i,mlx.sp->cc[i]);
			i++;
		}
		printf("r : %f\n", mlx.sp->r);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.sp->rgb[i]);
			i++;
		}
		mlx.sp = mlx.sp->next;
	}
}

void	ctest_cy(t_data mlx)
{
	int i;
	
	printf("\ntest cy\n");
	while (mlx.cy != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.cy->cc[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.cy->nc[i]);
			i++;
		}
		printf("r : %f\n", mlx.cy->r);
		printf("h : %f\n", mlx.cy->h);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.cy->rgb[i]);
			i++;
		}
		mlx.cy = mlx.cy->next;
	}
}

void	ctest_cr(t_data mlx)
{
	int i;
	
	printf("\ntest cr\n");
	while (mlx.cr != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("x[%d] : %f\n",i,mlx.cr->cc[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			printf("n[%d] : %f\n",i,mlx.cr->nc[i]);
			i++;
		}
		printf("r : %f\n", mlx.cr->r);
		printf("h : %f\n", mlx.cr->h);
		i = 0;
		while (i < 3)
		{
			printf("rgb[%d] : %d\n",i,mlx.cr->rgb[i]);
			i++;
		}
		mlx.cr = mlx.cr->next;
	}
}



