/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:01 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/30 17:24:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static void	position_n_distance(t_data *data)
{
	int i;
	int	j;

	i = -1;
	j = -1;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (data->worldMap[i][j] == 2)
			{
				data->enemies->pos_x = i;
				data->enemies->pos_y = j;
				data->enemies->distance = 
					pow((data->pos_X - data->enemies[i].pos_x), 2) +
                	pow(data->pos_X - data->enemies[i].pos_y, 2);
				data->enemies = data->enemies->next;
			}	
		}
	} 
}

static void	alloc_enemy_list(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->numb_of_enemies)
	{
		data->enemies = malloc(sizeof(t_enemy));
		data->enemies->id = i;
		data->enemies->enemy_hp = 4;
		data->enemies->next = NULL;
		data->enemies = data->enemies->next;
	}
}

void	enemies_ini(t_data *data)
{
	data->draw->gun_txt_idx = 5;
	data->gun_animation = 0;
	data->shoot_flag = 0;
	enemy_count(data);
	alloc_enemy_list(data);
	position_n_distance(data);
	order_enemies(data);
}

int	enemy_hit(t_data *data, int mapX, int mapY)
{
	while (data->enemies->next != NULL)
	{
		if (data->enemies->pos_x == mapX 
			&& data->enemies->pos_y == mapY)
		{
			data->enemies->enemy_hp--;
			data->shoot_flag = 1;
			if (data->enemies->enemy_hp == 0)
				return (0);
			else
				return (1);
		}
			data->enemies = data->enemies->next;
		}
	return (1);
}

void draw_enemies(t_data *data)
{
	int	sprite_x;
	int sprite_y;
	double transX;
	double transY;
	int	sprite_screenx;
	int texture_x;
	int texture_y;
	int i;
	int y;
	int d;
	uint32_t color;
	double	scale;

	i = -1;
	y = -1;
	scale = 1.0 / (data->plane_X * data->dir_vec_Y - data->dir_vec_X * data->plane_Y);
	while (++i < data->numb_of_enemies)
	{
		sprite_x = data->enemies->pos_x - data->pos_X;
		sprite_y = data->enemies->pos_y - data->pos_Y;
		transX = scale * (data->dir_vec_Y * sprite_x - data->dir_vec_X * sprite_y);
		transY = scale * (-data->plane_Y * sprite_x + data->plane_X * sprite_y);
		if (transY <= 0)
			continue ;
		sprite_screenx = (screenWidth / 2) * (1 + transX / transY);
		data->draw->line_h = fabs(data->draw->tex_h / transY);
		data->draw->start = -data->draw->line_h / 2 + screenHeight / 2;
		if (data->draw->start < 0)
			data->draw->start = 0;
		data->draw->end = data->draw->line_h / 2 + screenHeight / 2;
		if (data->draw->end >= screenHeight)
			data->draw->end = screenHeight - 1;
		sprite_x = -data->draw->tex_w / 2 + sprite_screenx;
		if (sprite_x < 0)
			sprite_x = 0;
		sprite_y = data->draw->tex_w / 2 + sprite_screenx;
		if (sprite_y >= screenWidth)
			sprite_y = screenWidth - 1;
		while (sprite_x < sprite_y)
		{
            texture_x = sprite_x - (-data->draw->tex_h / 2 + sprite_screenx);
			if (transY < data->distance_buffer[sprite_x] && sprite_x >= 0 && sprite_x < screenWidth)
			{
				y = -1;
				while (++y < data->draw->tex_h)
				{
					d = y * 256 - screenHeight * 128 + data->draw->tex_h * 128;
					texture_y = ((d * data->draw->tex_h) / data->draw->tex_h) / 256;
					color = *(uint32_t*)(data->draw->textures[4].addr +
                            (texture_y * data->draw->textures[4].line_len +
                            texture_x * (data->draw->textures[4].bpp / 8)));
					if (color != 0xFFFFFF)
						my_mlx_pixel_put(data->draw->img_buffer, sprite_x, data->draw->start + y, color);
				}
			}
			sprite_x++;
		}
	}
}
