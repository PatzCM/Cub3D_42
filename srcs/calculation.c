/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:39:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/21 18:21:04 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	calculate_ray_Dir(t_data *data, int x)
{
	data->vars->camera_X = 2 * x / data->vars->win_w - 1;
	data->vars->ray_DirX = data->dir_vec_X + data->plane_X * data->vars->camera_X;
	data->vars->ray_DirY = data->dir_vec_Y + data->plane_Y * data->vars->camera_X;
}
void	calculate_next(t_data *data)
{
	if (fabs(data->vars->ray_DirX) < 1e-9)
		data->vars->next_X = 1e30;
	else
		data->vars->next_X = fabs(1 / data->vars->ray_DirX);
	if (fabs(data->vars->ray_DirY) < 1e-9)
		data->vars->next_Y = 1e30;
	else
		data->vars->next_Y = fabs(1 / data->vars->ray_DirY);
}

void	calculate_side(t_data *data)
{
	t_calc_vars *vars;

	vars = data->vars;
	if (vars->ray_DirX < 0)
	{
	  vars->dir_stepX = -1;
	  vars->side_X = (data->pos_X - vars->mapX) * vars->next_X;
	}
	else
	{
	  vars->dir_stepX = 1;
	  vars->side_X = (vars->mapX + 1.0 - data->pos_X) * vars->next_X;
	}
	if (vars->ray_DirY < 0)
	{
	  vars->dir_stepY = -1;
	  vars->side_Y = (data->pos_Y - vars->mapY) * vars->next_Y;
	}
	else
	{
	  vars->dir_stepY = 1;
	  vars->side_Y = (vars->mapY + 1.0 - data->pos_Y) * vars->next_Y;
	}
}
void	check_walls(t_data *data)
{
	t_calc_vars *vars;

	vars = data->vars;
	while(vars->hit == 0)
	{
		if (vars->side_X < vars->side_Y)
		{
			vars->side_X += vars->next_X;
			vars->mapX += vars->dir_stepX;
			vars->side_hit = 0;
		}
		else
		{
			vars->side_Y += vars->next_Y;
			vars->mapY += vars->dir_stepY;
			vars->side_hit = 1;
		}
		if (data->worldMap[vars->mapX][vars->mapY] > 0)
			vars->hit = 1;
	}
}

void	calculate_perpendicular(t_data *data)
{
	t_calc_vars *vars;

	vars = data->vars;
	if (vars->side_hit == 0)
		vars->wall_dist = vars->side_X - vars->next_X;
	else
		vars->wall_dist = vars->side_Y - vars->next_Y;
}
