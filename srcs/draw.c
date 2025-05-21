/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:32:17 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/21 18:37:52 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	img_ini(t_data *data)
{
	data->draw->img.img = mlx_new_image(data->mlx, data->vars->win_w, data->vars->win_h);
	data->draw->img.addr = mlx_get_data_addr(data->draw->img.img, &data->draw->img.bpp, &data->draw->img.line_len, &data->draw->img.flag);
}

void	calculate_lines(t_data *data)
{
	t_draw_calc *draw;
	t_calc_vars *vars;
	
	draw = data->draw;
	vars = data->vars;
	draw->line_h = (int)(vars->win_h / vars->wall_dist);
	draw->start = -draw->line_h / 2 + vars->win_h / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + vars->win_h / 2;
	if (draw->end >= vars->win_h)
		draw->end = vars->win_h - 1;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	 if (x < 0 || x >= (img->line_len / (img->bpp / 8)) || y < 0 || y >= (img->line_len / (img->bpp / 8)))
        return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	clear_img(t_data *data, int color)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->vars->win_w)
	{
		j = -1;
		while (++j < data->vars->win_h)
			my_mlx_pixel_put(&data->draw->img, i, j, color);
	}
}

void	draw_line(t_data *data, int x)
{
	int y;
	int color;
	
	y = data->draw->start;
	while (++y < data->draw->end)
	{
		if (data->vars->side_hit == 0 && data->vars->dir_stepX == -1)
			color = 0x800000; //vermelho - sul
		else if (data->vars->side_hit == 0 && data->vars->dir_stepX == 1)
			color = 0x8080FF; //azul claro norte
		else if (data->vars->side_hit == 1 && data->vars->dir_stepY == -1)
			color = 0x800080; //roxo - este
		else if (data->vars->side_hit == 1 && data->vars->dir_stepY == 1)
			color = 0x808080; //cinza - oeste
		my_mlx_pixel_put(&data->draw->img, x, y, color);
	}
}