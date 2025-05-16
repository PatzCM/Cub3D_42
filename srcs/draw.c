/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:32:17 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/16 18:26:50 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	calculate_lines(t_data *data)
{
	t_draw_calc *draw;
	t_calc_vars *vars;
	
	draw = data->draw;
	vars = data->vars;
	draw->line_h = vars->win_h / vars->wall_dist;
	draw->start = (-(draw->line_h) / 2) + (vars->win_h / 2);
	if (draw->start < 0)
		draw->start = 0;
	draw->end = (draw->line_h / 2) + (vars->win_h / 2);
	if (draw->end >= vars->win_h)
		draw->end = vars->win_h - 1;
}

void	draw_line(t_data *data, int x, int worldMap[24][24])
{
	int y;
	int color;
	
	y = data->draw->start;
	while (++y < data->draw->end)
	{
		if (worldMap[data->vars->mapX][data->vars->mapY] == 1)
			color = 0xFF0000;
		else if (worldMap[data->vars->mapX][data->vars->mapY] == 2)
			color = 0x00FF00;
		mlx_pixel_put(data->mlx, data->win, x, y, color);
	}
}