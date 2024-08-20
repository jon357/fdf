/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:15:10 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:15:14 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	win_init(void)
{
	w.mt = 1;
	w.zm = 0.3;
	w.rt = 45;
	w.posx = 0;
	w.posy = 0;
	w.sizex = 3840 * 0.75;
	w.sizey = 2160 * 0.75;
	w.mx = w.sizey * 0.5;
	w.my = w.sizey * 0.5;
	w.mrg = w.sizey * w.zm;
	w.s = (w.sizey - (2 * w.mrg)) / (z.sizey - 1);
	w.mlx = mlx_init();
	w.img = mlx_new_image(w.mlx, w.sizex, w.sizey);
	w.addr = mlx_get_data_addr(w.img, &(w.bpp), &(w.line_len), &(w.endian));
	w.win = mlx_new_window(w.mlx, w.sizex, w.sizey, "mlx 42");
}

float	dp(float sx, float sy, float ex, float ey)
{
	return (sqrt(pow((ex - sx), 2) + pow((sy - ey), 2)));
}

int	lerp(int a, int b, float t)
{
	return ((int)((1 - t) * a + t * b));
}

void	put_pixel_img(int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < w.sizex && y < w.sizey)
	{
		dst = w.addr + (y * w.line_len + x * (w.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	tab_init(void)
{
	z.i = 0;
	z.tb = (int **)malloc(z.sizex * sizeof(int *));
	z.hx = (char ***)malloc(z.sizex * sizeof(char **));
	while (z.i < z.sizex)
	{
		z.tb[z.i] = (int *)malloc(z.sizey * sizeof(int));
		z.hx[z.i] = (char **)malloc(z.sizey * sizeof(char *));
		z.i++;
	}
}
