/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:02:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/23 16:11:13 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

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
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < (int)minimap_w)
	{
		j = -1;
		while (++j < (int)minimap_h)
			my_mlx_pixel_put(map, i, j, 0xFFFFFF);
	}
}

void	draw_minimap(t_data *data)
{
	int buff;

	buff = data->draw->startx;
	while (++(data->draw->starty) < data->draw->endy)
	{
		data->draw->startx = buff;
		while (++(data->draw->startx) < data->draw->endx)
			my_mlx_pixel_put(data->draw->img_buffer, data->draw->startx, data->draw->starty, 0xFFFFFF);
	}
}
