/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:15:33 by jcheca            #+#    #+#             */
/*   Updated: 2023/04/06 11:15:36 by jcheca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("ERREUR\nverrifier le nombre d'argument\n"));
	w.fd = open(argv[1], O_RDONLY);
	if (w.fd == -1)
		return (ft_printf("ERREUR\nverrifier le nom de la map\n"));
	get_size();
	tab_init();
	close(w.fd);
	w.fd = open(argv[1], O_RDONLY);
	split_map();
	win_init();
	close(w.fd);
	res();
	mlx_key_hook(w.win, deal_key, (void *)0);
	mlx_hook(w.win, 17, 0, (void *)kill_prog, 0);
	mlx_loop(w.mlx);
	return (0);
}
