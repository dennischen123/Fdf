/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:45:04 by dchen             #+#    #+#             */
/*   Updated: 2019/09/26 16:45:09 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_unit	iso(t_unit point)
{
	int tmp_x;
	int tmp_y;

	tmp_x = point.x;
	tmp_y = point.y;
	point.x = (tmp_x - tmp_y) * .8775;
	point.y = -(point.z) + (tmp_x + tmp_y) * .4794;
	return (point);
}
