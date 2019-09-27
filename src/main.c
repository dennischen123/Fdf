/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:10:09 by dchen             #+#    #+#             */
/*   Updated: 2019/09/06 20:08:59 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	int		fd;
	t_mlx	n_mlx;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			write(1, "NO FILE\n", 8);
			exit(0);
		}
		parse(fd, &(n_mlx.image));
		n_mlx.mlx = mlx_init();
		n_mlx.win = mlx_new_window(n_mlx.mlx, WIN_SIZE_X, WIN_SIZE_Y,
															WIN_TITLE);
		mlx_key_hook(n_mlx.win, key_pressed, &(n_mlx));
		print_controls(&n_mlx);
		create_image(&n_mlx);
		mlx_loop(n_mlx.mlx);
	}
	else
		write(1, "error\n", 6);
	return (0);
}

void	redraw(t_mlx *n_mlx)
{
	mlx_clear_window(n_mlx->mlx, n_mlx->win);
	print_controls(n_mlx);
	create_image(n_mlx);
}

void	print_controls(t_mlx *n_mlx)
{
	int y;

	y = 0;
	mlx_string_put(n_mlx->mlx, n_mlx->win, 50, y += 20, 0xFFFFFF,
													"User Instructions");
	mlx_string_put(n_mlx->mlx, n_mlx->win, 15, y += 20, 0xFFFFFF,
													"Zoom: +/-");
	mlx_string_put(n_mlx->mlx, n_mlx->win, 15, y += 20, 0xFFFFFF,
											"Move: Left & Right Arrows");
	mlx_string_put(n_mlx->mlx, n_mlx->win, 15, y += 20, 0xFFFFFF,
											"Depth: Up & down Arrows");
	mlx_string_put(n_mlx->mlx, n_mlx->win, 15, y += 20, 0xFFFFFF,
											"Isometric Projection: I");
	mlx_string_put(n_mlx->mlx, n_mlx->win, 15, y += 20, 0xFFFFFF,
											"Orthographic Projection: O");
}
