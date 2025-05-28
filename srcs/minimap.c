/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:02:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/26 14:33:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/* static void	draw_player(t_data *data, double scale, t_img *img)
{
	int minimap_px;
	int minimap_py;

	minimap_px = (int)(data->pos_X / scale);
	minimap_px = (int)(data->pos_Y / scale);
	
	
} */

void	ini_minimap(t_data *data)
{
	t_img *map;

	data->draw->minimap = malloc(sizeof(t_img));
	if (!data->draw->minimap)
		ft_exit(data);
	map = data->draw->minimap;
	map->img = mlx_new_image(data->mlx, (int)minimap_w, (int)minimap_h);
	map->addr = mlx_get_data_addr(map->img, &map->bpp, &map->line_len, &map->endian);
	if (!(map->addr))
		ft_exit(data);
}

void	draw_player(t_data *data)
{
	int playerx;
	int playery;
	double scale;
	int	i;
	int	j;
	
	i = -1;
	j = -1;
	scale = (double)mapWidth / (double)minimap_w;
	playerx = (int)(floor(data->pos_X / scale));
	playery = (int)(floor(data->pos_Y / scale));
	while (++i < minimap_player_size)
	{
		j = -1;
		while (++j < minimap_player_size)
			my_mlx_pixel_put(data->draw->minimap, playerx + i, playery + j, 0x00FF00);
	}
	
}

void	draw_minimap(t_data *data)
{
	int i;
	int j;
	double scale;

	scale = (double)mapWidth / (double)minimap_w;
	i = -1;
	j = -1;
	while (++i < minimap_w)
	{
		j = -1;
		while (++j < minimap_h)
		{
			if (i * scale < mapWidth && j * scale < mapHeight)
			{
				if (data->worldMap[(int)(floor(i * scale))][(int)floor(j * scale)] == 0)
					my_mlx_pixel_put(data->draw->minimap, i, j, 0xFFFFFF);
				else
					my_mlx_pixel_put(data->draw->minimap, i, j, 0xFF0000);
			}
			else
				continue ;
		}
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->draw->minimap->img, data->draw->minimap_startx, data->draw->minimap_starty);
}
