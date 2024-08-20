/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:15:22 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:15:25 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	v_reset(void)
{
	z.j = 0;
	while (z.j < w.sizey)
	{
		z.i = 0;
		while (z.i < w.sizex)
		{
			put_pixel_img(z.i, z.j, 0x000000);
			z.i++;
		}
		z.j++;
	}
}

int	*kill_prog(void)
{
	mlx_destroy_window(w.mlx, w.win);
	mlx_destroy_image(w.mlx, w.img);
	mlx_destroy_display(w.mlx);
	z.i = 0;
	while (z.i < z.sizex)
	{
		z.j = 0;
		while (z.j < z.sizey)
		{
			free(z.hx[z.i][z.j]);
			z.j++;
		}
		free(z.tb[z.i]);
		free(z.hx[z.i]);
		z.i++;
	}
	free(z.tb);
	free(z.hx);
	free(w.mlx);
	exit (0);
	return (0);
}

void	rot_scr(int rot)
{
	w.rt = w.rt + rot;
	if (w.rt < 0)
		w.rt = 345;
	if (w.rt >= 360)
		w.rt = 0;
}

void	sub_key(int key)
{
	int	scl;

	scl = 500;
	if (key == 119)
	{
		w.posy += scl;
	}
	else if (key == 100)
	{
		w.posx -= scl;
	}
	else if (key == 115)
	{
		w.posy -= scl;
	}
	else if (key == 97)
	{
		w.posx += scl;
	}
}

int	deal_key(int key)
{
	if (key == 65307)
		kill_prog();
	else if (key == 65361)
		rot_scr(-15);
	else if (key == 65363)
		rot_scr(15);
	else if (key == 65362)
		w.mt = w.mt + 0.2;
	else if (key == 65364)
		w.mt = w.mt - 0.2;
	else if (key == 119 || key == 100 || key == 115 || key == 97)
		sub_key(key);
	else if (key == 114)
		w.s++;
	else if (key == 102)
		w.s--;
	else
		return (key);
	v_reset();
	res();
	return (key);
}
