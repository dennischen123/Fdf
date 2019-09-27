/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:13:52 by dchen             #+#    #+#             */
/*   Updated: 2019/09/06 19:56:28 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		handle_error(int error)
{
	if (error == -1)
	{
		ft_putstr("No Data Found\n");
		exit(0);
	}
}

void		parse(int fd, t_img *img)
{
	char	*line;
	int		y;
	int		error;
	t_line	*current;

	y = 0;
	line = "empty";
	img->line_data = (t_line*)malloc(sizeof(t_line));
	ft_bzero(img->line_data, sizeof(t_line));
	current = img->line_data;
	if (get_next_line(fd, &line) > 0)
	{
		parse_helper(img, y, line, current);
		y++;
	}
	while ((error = get_next_line(fd, &line)) > 0)
	{
		current->next = (t_line*)malloc(sizeof(t_line));
		current->next->prev = current;
		current = current->next;
		parse_helper(img, y, line, current);
		y++;
	}
	handle_error(error);
}

void		parse_helper(t_img *img, int y, char *line, t_line *line_data)
{
	char		**line_arr;
	int			arr_size;
	int			x;
	int			z;

	line_arr = ft_strsplit(line, ' ');
	x = 0;
	arr_size = 0;
	while (line_arr[arr_size])
		arr_size++;
	line_data->units = (t_unit*)malloc(sizeof(t_unit) * arr_size);
	while (x < arr_size)
	{
		line_data->units[x].x = x;
		line_data->units[x].y = y;
		line_data->units[x].z = ft_atoi(line_arr[x]);
		z = line_data->units[x].z;
		x++;
		set_max_dimension(img, x, y, z);
	}
	free_line_arr(line_arr);
}

void		free_line_arr(char **line_arr)
{
	int i;

	i = 0;
	while (line_arr[i])
	{
		free(line_arr[i]);
		i++;
	}
}

void		set_max_dimension(t_img *img, int x, int y, int z)
{
	if (img->width < x)
		img->width = x;
	if (img->height < y)
		img->height = y;
	if (img->altitude < z)
		img->altitude = z;
}
