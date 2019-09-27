/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 04:49:58 by dchen             #+#    #+#             */
/*   Updated: 2019/09/26 04:50:03 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_mlx *n_mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(n_mlx->mlx, n_mlx->win);
		exit(0);
	}
	if (keycode == 126 || keycode == 125)
	{
		if (n_mlx->image.controls.zoom > 100)
			n_mlx->image.controls.zoom = 0;
		n_mlx->image.controls.zoom += (keycode == 126) ? .5 : -.5;
	}
	if (keycode == 69 || keycode == 78)
		n_mlx->image.controls.explode += (keycode == 69) ? 2 : -2;
	if (keycode == 123 || keycode == 124)
		n_mlx->image.controls.left_right += (keycode == 123) ? -10 : 10;
	if (keycode == 34 || keycode == 31)
		n_mlx->image.p_type = (keycode == 34) ? 0 : 1;
	redraw(n_mlx);
	return (0);
}
