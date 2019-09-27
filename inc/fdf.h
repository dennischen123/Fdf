/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:14:45 by dchen             #+#    #+#             */
/*   Updated: 2019/09/26 04:46:02 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 1600
# define WIN_TITLE "FDF"

typedef struct			s_vars
{
	int					del_x;
	int					del_y;
	int					x_da;
	int					y_da;
	int					error;
	int					tmp;
}						t_vars;

typedef struct			s_unit
{
	int					x;
	int					y;
	int					z;
}						t_unit;

typedef struct			s_line
{
	struct s_line		*prev;
	struct s_line		*next;
	size_t				size;
	t_unit				*units;
}						t_line;

typedef struct			s_control
{
	float				zoom;
	float				explode;
	int					up_down;
	int					left_right;
}						t_control;

typedef struct			s_img
{
	t_control			controls;
	int					size_line;
	t_line				*line_data;
	int					width;
	int					height;
	int					altitude;
	int					p_type;
}						t_img;

typedef	struct			s_mlx
{
	void				*mlx;
	void				*win;
	t_img				image;
}						t_mlx;

void					print_controls(t_mlx *n_mlx);
void					redraw(t_mlx *n_mlx);
t_unit					iso(t_unit point);
t_unit					translate(t_unit point, t_mlx n_mlx, int z_scale);
void					create_image(t_mlx *n_mlx);
void					create_image_2(t_mlx *n_mlx, t_line *cur);
void					draw_line(t_mlx n_mlx, t_unit pt1, t_unit pt2);
void					draw_line_2(t_mlx n_mlx, t_unit pt1, t_unit pt2,
															t_vars var);
int						key_pressed(int keycode, t_mlx *n_mlx);
void					free_line_arr(char **line_arr);
void					parse(int fd, t_img *img);
void					parse_helper(t_img *img, int y, char *line,
														t_line *line_data);
void					set_max_dimension(t_img *img, int x, int y, int z);

#endif
