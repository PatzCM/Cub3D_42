/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:40 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static void	reset_vars(t_data *data)
{
		data->vars->hit = 0;
		data->vars->mapX = (int)data->pos_X;
		data->vars->mapY = (int)data->pos_Y;
		data->vars->camera_X = 0;
		data->vars->ray_DirX = 0;
		data->vars->ray_DirY = 0;
		data->vars->next_X = 0;
		data->vars->next_Y = 0;
		data->vars->dir_stepX = 0;
		data->vars->dir_stepY = 0;
		data->vars->side_hit = 0;
		data->vars->wall_dist = 0;
		data->vars->side_X = 0;
		data->vars->side_Y = 0;
}
void	raycaster(t_data *data)
{
	int x;

	x = -1;
	while (++x < screenWidth)
	{
		reset_vars(data);
		calculate_ray_Dir(data, x);
		calculate_next(data);
		calculate_side(data);
		check_walls(data);
		calculate_perpendicular(data);
		calculate_lines(data);
		draw_line(data, x);
	}
}
