/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:32:17 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/22 19:11:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

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

	 if (x < 0 || x >= (int)screenWidth || y < 0 || y >= (int)screenHeight)
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
			my_mlx_pixel_put(data->draw->img_buffer, i, j, color);
	}
}