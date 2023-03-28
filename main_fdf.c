#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"

struct s_struc
{
	int		i;
	int		j;
	int		b;
	int		px;
	int		py;
	float	dp;
	float	sx;
	float	sy;
	float	rx;
	float	ry;
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
	float	mt;
	float	rt;
	int		sizex;
	int		sizey;
	int		mrgx;
	int		mrgy;
	int		mx;
	int		my;
}	w;

struct s_pos
{
	float	sx;
	float	sy;
	float	ex;
	float	ey;
}	s;

void	win_init(void)
{
	w.mt = 1;
	w.rt = 45;
	w.sizex = 3840 * 0.75;
	w.sizey = 2160 * 0.75;
	w.mx = w.sizex * 0.5;
	w.my = w.sizey * 0.5;
	w.mrgx = w.sizex * 0.2;
	w.mrgy = w.sizey * 0.2;
	z.rx = 2 * w.mrgx;
	z.ry = 2 * w.mrgy;
	z.sx = (w.sizex - z.rx) / (z.sizex - 1);
	z.sy = (w.sizey - z.ry) / (z.sizey - 1);
	w.mlx = mlx_init();
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
		mlx_pixel_put(w.mlx, w.win, z.pftwx, z.pftwy, z.color);
		z.i++;
	}
}

void	deplacer_point(float psx, float psy, float pex, float pey)
{
	float	a;
	float	dx;
	float	dy;

	a = w.rt * M_PI / 180.0;
	dx = psx - w.mx;
	dy = psy - w.my;
	s.sx = w.mx + dx * cos(a) - dy * sin(a);
	s.sy = w.my + dx * sin(a) + dy * cos(a);
	dx = pex - w.mx;
	dy = pey - w.my;
	s.ex = w.mx + dx * cos(a) - dy * sin(a);
	s.ey = w.my + dx * sin(a) + dy * cos(a);
}

void	draw_tab(void)
{
	if (z.px + 1 < z.sizex)
	{
		z.ecolor = hextoint(z.hx[z.px + 1][z.py]);
		s.sx = w.mrgx + z.px * z.sx;
		s.sy = w.mrgy + z.py * z.sy ;
		s.ex = w.mrgx + (z.px + 1) * z.sx;
		s.ey = w.mrgy + z.py * z.sy;
		deplacer_point(s.sx, s.sy, s.ex, s.ey);
		pftw(s.sx, s.sy - (z.tb[z.px][z.py] * w.mt),
			s.ex, s.ey - (z.tb[z.px + 1][z.py] * w.mt));
	}
	if (z.py + 1 < z.sizey)
	{
		z.ecolor = hextoint(z.hx[z.px][z.py + 1]);
		s.sx = w.mrgx + z.px * z.sx;
		s.sy = w.mrgy + z.py * z.sy;
		s.ex = w.mrgx + z.px * z.sx;
		s.ey = w.mrgy + (z.py + 1) * z.sy;
		deplacer_point(s.sx, s.sy, s.ex, s.ey);
		pftw(s.sx, s.sy - (z.tb[z.px][z.py] * w.mt),
			s.ex, s.ey - (z.tb[z.px][z.py + 1] * w.mt));
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
		draw_orient(z.sizex - 1 ,z.sizey - 1 , -1, -1);
	}
	if (w.rt >= 270 && w.rt < 360)
	{
		z.ex = -1;
		z.ey = z.sizey;
		draw_orient(z.sizex - 1, 0, 1, -1);
	}
}

void	debug_struc_matri(void)
{
	z.j = 0;
	while (z.j < z.sizey)
	{
		z.i = 0;
		while (z.i < z.sizex)
		{
			ft_printf("|-%d-%d-|", z.i, z.j);
			ft_printf("%d", z.tb[z.i][z.j]);
			ft_printf("%s", z.hx[z.i][z.j]);
			z.i++;
		}
		z.j++;
		ft_printf("\n");
	}
}

int	lst_len(char **list)
{
	z.i = 0;
	while (list[z.i])
		z.i++;
	return (z.i);
}

void	get_size(void)
{
	z.str = get_next_line(w.fd);
	z.list = ft_split(z.str, ' ');
	z.i = 0;
	while (z.list[z.i])
	{
		z.i++;
	}
	z.j = 0;
	while (z.str)
	{
		z.str = get_next_line(w.fd);
		z.j++;
	}
	z.sizex = z.i;
	z.sizey = z.j;
}

void	tab_init(void)
{
	z.i = 0;
	z.tb = malloc(z.sizex * sizeof(int *));
	while (z.i < z.sizex)
	{
		z.tb[z.i++] = malloc(z.sizey * sizeof(int));
	}
	z.i = 0;
	z.hx = (char ***)malloc(z.sizex * sizeof(char **));
	while (z.i < z.sizex)
	{
		z.hx[z.i] = (char **)malloc(z.sizey * sizeof(char *));
		z.j = 0;
		while (z.j < z.sizey)
		{
			z.hx[z.i][z.j++] = (char *)malloc(10 * sizeof(char));
		}
		z.i++;
	}
}

void	split_map(void)
{
	z.j = 0;
	z.str = get_next_line(w.fd);
	while (z.str)
	{
		z.list = ft_split(z.str, ' ');
		z.i = 0;
		while (z.list[z.i] && z.i < z.sizex)
		{
			if (ft_strchr(z.list[z.i], ','))
			{
				z.tb[z.i][z.j] = ft_atoi(ft_split(z.list[z.i], ',')[0]);
				z.hx[z.i][z.j] = ft_split(z.list[z.i], ',')[1];
			}
			else
			{
				z.tb[z.i][z.j] = ft_atoi(z.list[z.i]);
				z.hx[z.i][z.j] = "0xFFFFFF";
			}
			z.i++;
		}
		z.j++;
		z.str = get_next_line(w.fd);
	}
}

void	v_reset(void)
{
	z.j = 0;
	while (z.j < w.sizey)
	{
		z.i = 0;
		while (z.i < w.sizex)
		{
			mlx_pixel_put(w.mlx, w.win, z.i++, z.j, 0x000000);
		}
		z.j++;
	}
}

int	deal_key(int key)
{
	if (key == 65307)
	{
		mlx_destroy_window(w.mlx, w.win);
		exit (0);
		return (0);
	}
	if (key == 65361)
	{
		v_reset();
		w.rt = w.rt - 15;
		if (w.rt < 0)
			w.rt = 345;
		res();
	}
	if (key == 65362)
	{
		v_reset();
		w.mt = w.mt + 0.2;
		res();
	}
	if (key == 65363)
	{
		v_reset();
		w.rt = w.rt + 15;
		if (w.rt >= 360)
			w.rt = 0;
		res();
	}
	if (key == 65364)
	{
		v_reset();
		w.mt = w.mt - 0.2;
		res();
	}
	if (key == 111)
	{
		ft_printf("%d %d\n", w.mx, w.my);
	}
	//ft_printf("%d", key);
	return (key);
}

int	main(void)
{
	char	*map;

	//map = "test_maps/MGDS_AMAZONIA_OCEAN1_S.fdf";
	//map = "test_maps/MGDS_WHOLE_WORLD_OCEAN1_S.fdf";
	//map = "test_maps/MGDS_HIMALAYA_OCEAN1_M.fdf";
	//map = "test_maps/USGS_ULCN2005_grid.txt_OCEAN1_S.fdf";
	//map = "test_maps/USGS_ULCN2005_grid.txt_OCEAN1_M.fdf";
	//map = "test_maps/10-2.fdf";
	//map = "test_maps/mars.fdf";
	//map = "test_maps/elem-col.fdf";
	//map = "test_maps/42.fdf";
	//map = "test_maps/50-4.fdf";
	//map = "test_maps/100-6.fdf";
	map = "test_maps/t2.fdf";
	//map = "test_maps/t1.fdf";
	//map = "test_maps/julia.fdf";
	//map = "test_maps/elem-fract.fdf";
	w.fd = open(map, O_RDONLY);
	get_size();
	tab_init();
	close(w.fd);
	w.fd = open(map, O_RDONLY);
	split_map();
	//debug_struc_matri();
	win_init();
	res();
	mlx_key_hook(w.win, deal_key, (void *)0);
	//mlx_mouse_hook(w.win, mouse_houk, (void *)0);
	mlx_loop(w.mlx);
	return (0);
}
