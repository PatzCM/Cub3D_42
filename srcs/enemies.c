/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:01 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/02 16:21:55 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static void	position_n_distance(t_data *data)
{
	int i;
	int	j;
	t_enemy *tmp;

	i = -1;
	j = -1;
	tmp = data->enemies;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (data->worldMap[i][j] == 2)
			{
				tmp->pos_x = (double)i + 0.5;
				tmp->pos_y = (double)j + 0.5;
				tmp->distance = 
					pow((data->pos_X - tmp->pos_x), 2) +
                	pow(data->pos_Y - tmp->pos_y, 2);
				tmp = tmp->next;
			}	
		}
	} 
}

static void	alloc_enemy_list(t_data *data)
{
	int i;
	t_enemy *new;
	t_enemy *current;
	
	i = -1;
	current = NULL;
	new = NULL;
	data->enemies = NULL;
	while (++i < data->numb_of_enemies)
	{
		new = malloc(sizeof(t_enemy));
		new->id = i;
		new->enemy_hp = 4;
		new->next = NULL;
		new->prev = NULL;
		if (current == NULL)
		{
			current = new;
			data->enemies = new;
		}
		else
		{
			current->next = new;
			new->prev = current;
			current = current->next;
		}
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
	t_enemy *current;

	current = data->enemies;
	while (current->next != NULL)
	{
		if (current->pos_x == mapX 
			&& current->pos_y == mapY)
		{
			current->enemy_hp--;
			data->shoot_flag = 1;
			if (current->enemy_hp == 0)
				return  (0);
			else
				return (1);
			current = current->next;
		}
	}
	return (1);
}

void draw_enemies(t_data *data)
{
	t_enemy *current;
	int	sprite_x;
	int sprite_y;
	double transX;
	double transY;
	int texture_x;
	int texture_y;
	int drawstartx;
	int drawstarty;
	int	sprite_screenx;
	int y;
	int d;
	uint32_t color;
	double	scale;

	y = -1;
	data->draw->tex_h = 64;
	data->draw->tex_w = 64;
	current = data->enemies;
	scale = 1.0 / (data->plane_X * data->dir_vec_Y - data->dir_vec_X * data->plane_Y);
	while (current)
	{
		sprite_x = (int)current->pos_x - data->pos_X;
		sprite_y = (int)current->pos_y - data->pos_Y;
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
		drawstartx = -data->draw->line_h / 2 + sprite_screenx;
		if (drawstartx < 0)
			drawstartx = 0;
		drawstarty = data->draw->line_h / 2 + sprite_screenx;
		if (drawstarty >= screenWidth)
			drawstarty = screenWidth - 1;
		sprite_x = drawstartx;
		while (sprite_x < drawstarty)
		{
			if (transY < data->distance_buffer[sprite_x] && sprite_x >= 0 && sprite_x < screenWidth)
			{
				texture_x = (int)(256 * (sprite_x - drawstartx) * 64 / data->draw->line_h / 256);
				y = data->draw->start - 1;
				while (++y < data->draw->end)
				{
					d = (y - data->draw->start) * 256 - screenHeight * 128 + data->draw->line_h * 128;
					texture_y = ((d * 64) / data->draw->line_h) / 256;
					color = *(uint32_t*)(data->draw->textures[4].addr +
                            (texture_y * data->draw->textures[4].line_len +
                            texture_x * (data->draw->textures[4].bpp / 8)));
					if (color != 0xFFFFFF)
						my_mlx_pixel_put(data->draw->img_buffer, sprite_x, y, color);
				}
			}
			sprite_x++;
		}
		current = current->next;
	}
}
