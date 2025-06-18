/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:31:46 by palexand          #+#    #+#             */
/*   Updated: 2025/06/16 18:14:03 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->max_height
		|| y > (int)(ft_strlen(data->map->map[x]) - 1))
		return (x >= 0 && y >= 0
			&& x < data->map->max_height
			&& y < (int)(ft_strlen(data->map->map[x]) - 1)
			&& data->map->map[x][y] == '1');
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == 'X')
		return (TRUE);
	data->map->map[x][y] = 'X';
	if (!flood_fill(data, x + 1, y))
		return (FALSE);
	if (!flood_fill(data, x - 1, y))
		return (FALSE);
	if (!flood_fill(data, x, y + 1))
		return (FALSE);
	if (!flood_fill(data, x, y - 1))
		return (FALSE);
	return (TRUE);
}

int	ft_strchr_player(char *line)
{
	if (ft_strchr(line, 'S'))
		return (ft_strchr_len(line, 'S'));
	if (ft_strchr(line, 'N'))
		return (ft_strchr_len(line, 'N'));
	if (ft_strchr(line, 'E'))
		return (ft_strchr_len(line, 'E'));
	if (ft_strchr(line, 'W'))
		return (ft_strchr_len(line, 'W'));
	return (0);
}

void	fill_blank(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->max_height
		|| y > (int)(ft_strlen(data->map->map[x]) - 1))
		return ;
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == '0'
		|| data->map->map[x][y] == 'H')
		return ;
	if (data->map->map[x][y] == 'X')
		data->map->map[x][y] = '0';
	fill_blank(data, x + 1, y);
	fill_blank(data, x - 1, y);
	fill_blank(data, x, y + 1);
	fill_blank(data, x, y - 1);
}

bool	check_flood(t_data *data)
{
	int		i;

	i = -1;
	if (!flood_fill(data, data->player->x_pos, data->player->y_pos))
	{
		return (ft_putstr_fd("Error!\nMap is not closed\n", 2), FALSE);
	}
	find_outer(data);
	fill_blank(data, data->player->x_pos, data->player->y_pos);
	return (TRUE);
}
