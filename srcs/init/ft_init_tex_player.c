/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tex_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:48:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:37:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_init_minimap(t_data *data)
{
	data->img_minimap = malloc(sizeof(t_img));
	if (!data->img_minimap)
		ft_free(-1, data);
	data->img_minimap->img = NULL;
	data->img_minimap->img = mlx_new_image(data->mlx, data->minimap_width,
			data->minimap_height);
	if (!data->img_minimap->img)
		ft_free(-1, data);
	data->img_minimap->addr = (int *)mlx_get_data_addr(data->img_minimap->img,
			&data->img_minimap->pixel_bits, &data->img_minimap->size_line,
			&data->img_minimap->endian);
}

void	ft_init_player(t_data *data)
{
	int		i;
	int		j;
	int		player;

	i = -1;
	player = 0;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			if (data->map->map[i][j] == 'S' || data->map->map[i][j] == 'N' ||
					data->map->map[i][j] == 'E' ||
					data->map->map[i][j] == 'W')
				ft_init_player_utils(data, data->map->map[i][j], i, &player);
		}
	}
	if (player != 1)
	{
		ft_putstr_fd("Error\nInvalid number of Players\n", 2);
		ft_free(1, data);
	}
}

void	ft_init_tex_wall(t_data *data)
{
	data->tex_north = malloc(sizeof(t_img));
	if (!data->tex_north)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_north, data->map_data->no);
	data->tex_south = malloc(sizeof(t_img));
	if (!data->tex_south)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_south, data->map_data->so);
	data->tex_east = malloc(sizeof(t_img));
	if (!data->tex_east)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_east, data->map_data->ea);
	data->tex_west = malloc(sizeof(t_img));
	if (!data->tex_west)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_west, data->map_data->we);
	data->tex_door = malloc(sizeof(t_img));
	if (!data->tex_door)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_door, "textures/door.xpm");
	data->hex_ceiling = data->map_data->color_c;
	data->hex_floor = data->map_data->color_f;
}

void	ft_start_tex(t_data *data, t_img *img, char *file)
{
	img->img = NULL;
	img->img = mlx_xpm_file_to_image(data->mlx, file, &img->x, &img->y);
	if (!img->img)
	{
		ft_putstr_fd("Error\nInvalid Textures/Colors!\n", 2);
		ft_free(1, data);
	}
	img->addr = (int *)mlx_get_data_addr(img->img,
			&img->pixel_bits, &img->size_line, &img->endian);
}
