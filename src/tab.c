/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:15:42 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:15:45 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	res(void)
{
	if (w.rt >= 0 && w.rt < 90)
	{
		z.ex = z.sizex;
		z.ey = z.sizey;
		draw_orient(0, 0, 1, 1);
	}
	if (w.rt >= 90 && w.rt < 180)
	{
		z.ex = z.sizex;
		z.ey = -1;
		draw_orient(0, z.sizey - 1, -1, 1);
	}
	if (w.rt >= 180 && w.rt < 270)
	{
		z.ex = -1;
		z.ey = -1;
		draw_orient(z.sizex - 1, z.sizey - 1, -1, -1);
	}
	if (w.rt >= 270 && w.rt < 360)
	{
		z.ex = -1;
		z.ey = z.sizey;
		draw_orient(z.sizex - 1, 0, 1, -1);
	}
	mlx_put_image_to_window (w.mlx, w.win, w.img, 0, 0);
}

void	get_size(void)
{
	z.str = get_next_line(w.fd);
	z.list = ft_split(z.str, ' ');
	z.i = 0;
	while (z.list[z.i])
	{
		free(z.list[z.i]);
		z.i++;
	}
	free(z.list[z.i]);
	z.j = 0;
	while (z.str)
	{
		free(z.str);
		z.str = get_next_line(w.fd);
		z.j++;
	}
	z.sizex = z.i;
	z.sizey = z.j;
	free(z.list);
	free(z.str);
}

void	sub_split(void)
{
	if (ft_strchr(z.list[z.i], ','))
	{
		z.split_r = ft_split(z.list[z.i], ',');
		z.tb[z.i][z.j] = ft_atoi(z.split_r[0]);
		z.hx[z.i][z.j] = ft_strdup(z.split_r[1]);
		free(z.split_r[1]);
		free(z.split_r[0]);
		free(z.split_r);
	}
	else
	{
		z.tb[z.i][z.j] = ft_atoi(z.list[z.i]);
		z.hx[z.i][z.j] = ft_strdup("0xFFFFFF");
	}
}

void	exit_crash(void)
{
	while (z.i >= 0)
		free(z.list[z.i--]);
	free(z.list);
	free(z.str);
	while (z.str)
	{
		z.str = get_next_line(w.fd);
		free(z.str);
	}
	free(get_next_line(w.fd));
	z.i = 0;
	while (z.i < z.sizex)
	{
		z.j = 0;
		while (z.j < z.sizey)
			free(z.hx[z.i][z.j++]);
		free(z.tb[z.i]);
		free(z.hx[z.i]);
		z.i++;
	}
	free(z.tb);
	free(z.hx);
	exit(0);
}

void	split_map(void)
{
	z.str = get_next_line(w.fd);
	z.j = 0;
	while (z.str)
	{
		z.list = ft_split(z.str, ' ');
		z.i = 0;
		while (z.list[z.i])
			z.i++;
		if (z.i != z.sizex)
			exit_crash();
		z.i = 0;
		while (z.list[z.i] && z.i < z.sizex)
		{
			sub_split();
			free(z.list[z.i]);
			z.i++;
		}
		free(z.list[z.i]);
		free(z.list);
		z.j++;
		free(z.str);
		z.str = get_next_line(w.fd);
	}
	free(z.str);
}
