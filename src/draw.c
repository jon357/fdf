/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:15:00 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:15:03 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	pftw(float sx, float sy, float ex, float ey)
{
	z.unbi = atan2((ey - sy), (ex - sx));
	z.i = 0;
	z.dp = dp(sx, sy, ex, ey);
	z.ecr = 0;
	z.ecg = 0;
	z.ecb = 0;
	while (z.i < z.dp)
	{
		z.ecr = lerp((z.scolor >> 16) & 0xff,
				(z.ecolor >> 16) & 0xff, (float)z.i / z.dp);
		z.ecg = lerp((z.scolor >> 8) & 0xff,
				(z.ecolor >> 8) & 0xff, (float)z.i / z.dp);
		z.ecb = lerp(z.scolor & 0xff, z.ecolor & 0xff, (float)z.i / z.dp);
		z.color = (z.ecr << 16) | (z.ecg << 8) | z.ecb;
		z.pftwx = (sx + z.i * cos(z.unbi));
		z.pftwy = (sy + z.i * sin(z.unbi));
		put_pixel_img(z.pftwx, z.pftwy, z.color);
		z.i++;
	}
}

void	pivot_point(float psx, float psy, float pex, float pey)
{
	float	a;
	float	dx;
	float	dy;

	a = w.rt * M_PI / 180.0;
	dx = psx - w.mx + 500;
	dy = psy - w.my + 500;
	s.sx = w.mx + dx * cos(a) - dy * sin(a);
	s.sy = w.my + dx * sin(a) + dy * cos(a);
	dx = pex - w.mx + 500;
	dy = pey - w.my + 500;
	s.ex = w.mx + dx * cos(a) - dy * sin(a);
	s.ey = w.my + dx * sin(a) + dy * cos(a);
}

int	hextoint(char *str)
{
	z.i = 1;
	z.temp = 0;
	while (str[++z.i])
	{
		z.b = str[z.i];
		if (z.b == '\n')
			return (z.temp);
		if (z.b >= '0' && z.b <= '9')
			z.b = z.b - '0';
		else if (z.b >= 'a' && z.b <= 'f')
			z.b = z.b - 'a' + 10;
		else if (z.b >= 'A' && z.b <= 'F')
			z.b = z.b - 'A' + 10;
		z.temp = (z.temp << 4) | (z.b & 0xF);
	}
	return (z.temp);
}

void	draw_tab(void)
{
	if (z.px + 1 < z.sizex)
	{
		z.ecolor = hextoint(z.hx[z.px + 1][z.py]);
		s.sx = z.px * w.s;
		s.sy = z.py * w.s;
		s.ex = (z.px + 1) * w.s;
		s.ey = z.py * w.s;
		pivot_point(s.sx, s.sy, s.ex, s.ey);
		pftw(s.sx + w.posx, s.sy - (z.tb[z.px][z.py] * w.mt) + w.posy,
			s.ex + w.posx, s.ey - (z.tb[z.px + 1][z.py] * w.mt) + w.posy);
	}
	if (z.py + 1 < z.sizey)
	{
		z.ecolor = hextoint(z.hx[z.px][z.py + 1]);
		s.sx = z.px * w.s;
		s.sy = z.py * w.s;
		s.ex = z.px * w.s;
		s.ey = (z.py + 1) * w.s;
		pivot_point(s.sx, s.sy, s.ex, s.ey);
		pftw(s.sx + w.posx, s.sy - (z.tb[z.px][z.py] * w.mt) + w.posy,
			s.ex + w.posx, s.ey - (z.tb[z.px][z.py + 1] * w.mt) + w.posy);
	}
}

void	draw_orient(int s1, int s2, int ystep, int xstep)
{
	z.px = s1;
	while (z.px != z.ex)
	{
		z.py = s2;
		while (z.py != z.ey)
		{
			z.scolor = hextoint(z.hx[z.px][z.py]);
			draw_tab();
			z.py += ystep;
		}
		z.px += xstep;
	}
}
