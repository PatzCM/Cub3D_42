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

bool	check_flood(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	data->map->fmap = ft_calloc(sizeof(char *), data->map->max_height + 1);
	while (data->map->map[++i])
		data->map->fmap[i] = ft_strdup(data->map->map[i]);
	data->map->fmap[i] = NULL;
	tmp = data->map->map;
	data->map->map = data->map->fmap;
	if (!flood_fill(data, data->player->x_pos, data->player->y_pos))
	{
		data->map->map = tmp;
		ft_matrix_free((void **) data->map->fmap);
		return (ft_putstr_fd("Error!\nMap is not closed\n", 2), FALSE);
	}
	data->map->map = tmp;
	ft_matrix_free((void **) data->map->fmap);
	return (TRUE);
}
