/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:31:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/22 18:59:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

int	ft_exit(t_data *data)
{
	int i;

	i = -1;
	while(++i < 4)
		mlx_destroy_image(data->mlx, data->draw->textures[i].img);
	if (data->draw->img_buffer->img)
		mlx_destroy_image(data->mlx, data->draw->img_buffer->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	i = -1;
	if (data->worldMap)
	{
		while (data->worldMap[++i])
			free(data->worldMap[i]);
		free(data->worldMap);
	}
	if (data->draw->img_buffer)
		free(data->draw->img_buffer);
	if (data->vars)
		free(data->vars);
	if (data->draw)
		free(data->draw);
	if (data)
		free(data);
	exit(0);
}