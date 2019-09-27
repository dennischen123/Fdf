/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:06:30 by dchen             #+#    #+#             */
/*   Updated: 2019/09/26 16:06:33 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_mlx n_mlx, t_unit pt1, t_unit pt2)
{
	t_vars var;

	var.del_x = abs(pt2.x - pt1.x);
	var.del_y = abs(pt2.y - pt1.y);
	var.x_da = pt1.x < pt2.x ? 1 : -1;
	var.y_da = pt1.y < pt2.y ? 1 : -1;
	var.error = (var.del_x > var.del_y ? var.del_x : -(var.del_y)) / 2;
	draw_line_2(n_mlx, pt1, pt2, var);
}

void	draw_line_2(t_mlx n_mlx, t_unit pt1, t_unit pt2, t_vars var)
{
	while (1)
	{
		if ((pt1.x >= WIN_SIZE_X || pt1.y >= WIN_SIZE_Y) ||
										(pt1.x < 0 || pt1.y < 0))
			break ;
		mlx_pixel_put(n_mlx.mlx, n_mlx.win, pt1.x, pt1.y, 0x00FFFFFF);
		if (pt1.x == pt2.x && pt1.y == pt2.y)
			break ;
		var.tmp = var.error;
		if (var.tmp > -(var.del_x))
		{
			var.error -= var.del_y;
			pt1.x += var.x_da;
		}
		if (var.tmp < var.del_y)
		{
			var.error += var.del_x;
			pt1.y += var.y_da;
		}
	}
}

void	create_image(t_mlx *n_mlx)
{
	t_line		*cur;
	int			y;

	y = 0;
	cur = n_mlx->image.line_data;
	while (y < n_mlx->image.height)
	{
		create_image_2(n_mlx, cur);
		cur = cur->next;
		y++;
	}
}

void	create_image_2(t_mlx *n_mlx, t_line *cur)
{
	t_unit		tmp1;
	t_unit		tmp2;
	int			i;
	int			z_scale;

	if (n_mlx->image.altitude > 25)
		z_scale = n_mlx->image.altitude / (n_mlx->image.altitude * .75);
	else if (n_mlx->image.altitude > 10)
		z_scale = n_mlx->image.altitude / (n_mlx->image.altitude * .3);
	else
		z_scale = n_mlx->image.altitude / (n_mlx->image.altitude * .1);
	z_scale += n_mlx->image.controls.zoom;
	i = -1;
	while (++i < n_mlx->image.width)
	{
		tmp1 = translate(cur->units[i], *n_mlx, z_scale);
		if (i + 1 < n_mlx->image.width)
		{
			tmp2 = translate(cur->units[i + 1], *n_mlx, z_scale);
			draw_line(*n_mlx, tmp1, tmp2);
		}
		if (cur->prev)
			tmp2 = translate(cur->prev->units[i], *n_mlx, z_scale);
		draw_line(*n_mlx, tmp1, tmp2);
	}
}

t_unit	translate(t_unit point, t_mlx n_mlx, int z_scale)
{
	int total_used_x;
	int total_used_y;

	total_used_x = (WIN_SIZE_X / (n_mlx.image.width * 2.5))
												* n_mlx.image.width;
	total_used_y = (WIN_SIZE_Y / (n_mlx.image.height * 2.5))
												* n_mlx.image.height;
	point.z *= z_scale;
	point.x *= (total_used_y / n_mlx.image.width) +
								n_mlx.image.controls.explode;
	point.y *= (total_used_y / n_mlx.image.width) +
								n_mlx.image.controls.explode;
	point.x += WIN_SIZE_X / 1.5;
	point.x += n_mlx.image.controls.left_right;
	if (n_mlx.image.p_type == 1)
	{
		point.y += WIN_SIZE_Y / 6;
		return (point);
	}
	point = iso(point);
	return (point);
}
