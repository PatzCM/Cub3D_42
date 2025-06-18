/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_blank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:22:09 by palexand          #+#    #+#             */
/*   Updated: 2025/06/18 12:22:30 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	fill_blank(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->max_height - 1
		|| y > (int)(ft_strlen(data->map->map[x]) - 1))
		return ;
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == '0')
		return ;
	if (data->map->map[x][y] == ' ')
		data->map->map[x][y] = '0';
	fill_blank(data, x + 1, y);
	fill_blank(data, x - 1, y);
	fill_blank(data, x, y + 1);
	fill_blank(data, x, y - 1);
}

void	fill_outer(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->max_height - 1
		|| y > (int)(ft_strlen(data->map->map[x]) - 1))
		return ;
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == 'X')
		return ;
	if (data->map->map[x][y] == ' ' || data->map->map[x][y] == '0')
		data->map->map[x][y] = '1';
	fill_blank(data, x + 1, y);
	fill_blank(data, x - 1, y);
	fill_blank(data, x, y + 1);
	fill_blank(data, x, y - 1);
}

void	find_outer(t_data *data)
{
	int x;
	int y;

	x = -1;
	while (data->map->map[++x])
	{
		y = -1;
		while (data->map->map[x][++y])
		{
			if (data->map->map[x][y] == ' ' 
				|| data->map->map[x][y] == '0')
			{
				data->map->map[x][y] = 'X';
				fill_blank(data, x, y);
				x = -1;
				break ;
			}
		}
	}
}
