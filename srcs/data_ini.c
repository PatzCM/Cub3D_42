/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:08:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/21 17:33:50 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static void	keys_ini(t_data *data)
{
	data->keys[0] = false;
	data->keys[1] = false;
	data->keys[2] = false;
	data->keys[3] = false;
}

static void	vars_ini(t_data *data)
{
	data->pos_X = 22;
	data->pos_Y = 12;
	data->curr_time = 0;
	data->old_time = 0;
	data->vars->win_w = screenWidth;
	data->vars->win_h = screenHeight;
	data->delta_time = 0;
	data->dir_vec_X = -1;
	data->dir_vec_Y = 0;
	data->plane_X = 0;
	data->plane_Y = 0.66;
	data->vars->side_X = 0;
	data->vars->side_Y = 0;
}

static void	draw_ini(t_data *data)
{
	data->draw->img.img = mlx_new_image(data->mlx, data->vars->win_w, data->vars->win_h);
	if (!data->draw->img.img)
		ft_exit(data);
	data->draw->end = 0;
	data->draw->start = 0;
	data->draw->line_h = 0;
}
static void	window_ini(t_data *data)
{
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Cub3d da Nasa");
	if (!(data->win))
		ft_exit(data);
}
/**
	@brief inicicializes the main data struct
	
	pos_X and pos_Y are the player start position
	dir_vec_X and Y are the direction of the first vector
	plane X and Y make the 2d plane to use in the raycasting
	curr_time is the time of the current frame
	old_time is the time of the last frame
	@param data is the main data struct
 */

void	data_ini(t_data *data)
{
	int worldMap[mapWidth][mapHeight]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	data->worldMap = malloc(sizeof(int *) * mapWidth);
	for (int i = 0; i < mapWidth; i++) 
	{
    	data->worldMap[i] = malloc(sizeof(int) * mapHeight);
    	for (int j = 0; j < mapHeight; j++) {
       		data->worldMap[i][j] = worldMap[i][j];
    }
	}
	data->mlx = mlx_init();
	if (!(data->mlx))
		ft_exit(data);
	window_ini(data);
	data->vars = malloc(sizeof(t_calc_vars));
	data->draw = malloc(sizeof(t_draw_calc));
	if (!data->vars || !data->draw)
		ft_exit(data);
	vars_ini(data);
	draw_ini(data);
	keys_ini(data);
	img_ini(data);
}
