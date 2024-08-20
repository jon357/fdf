/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:16:40 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:17:36 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

struct s_struc
{
	int		i;
	int		j;
	int		b;
	int		px;
	int		py;
	float	dp;
	int		ex;
	int		ey;
	int		sizex;
	int		sizey;
	int		color;
	int		scolor;
	int		ecolor;
	int		temp;
	int		ecr;
	int		ecg;
	int		ecb;
	int		**tb;
	char	*str;
	char	**split_r;
	char	**list;
	char	***hx;
	float	unbi;
	float	pftwx;
	float	pftwy;
}	z;

struct s_wi
{
	int		fd;
	void	*mlx;
	void	*win;
	void	*img;
	float	mt;
	float	rt;
	float	zm;
	float	s;
	int		sizex;
	int		sizey;
	int		mrg;
	int		mx;
	int		my;
	int		posx;
	int		posy;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}	w;

struct s_pos
{
	float	sx;
	float	sy;
	float	ex;
	float	ey;
}	s;

void	win_init(void);
int		*kill_prog(void);
float	dp(float sx, float sy, float ex, float ey);
int		lerp(int a, int b, float t);
void	draw_orient(int s1, int s2, int ystep, int xstep);
void	res(void);
void	get_size(void);
void	tab_init(void);
void	split_map(void);
void	v_reset(void);
int		deal_key(int key);
void	put_pixel_img(int x, int y, int color);

#endif
