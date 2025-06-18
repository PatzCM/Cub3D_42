/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:38:18 by palexand          #+#    #+#             */
/*   Updated: 2025/06/18 14:38:18 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	ft_count_comma(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!line)
		return (i);
	while (line[++i])
		if (line[i] == ',')
			count++;
	return (count);
}

bool	ft_ver_col_return(char **map, double tempx,
					double tempy, t_data *data)
{
	return (map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] != '1'
		&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& map[(int)tempx][(int)tempy] != '1'
		&& map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] != ' '
		&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != ' '
		&& map[(int)tempx][(int)tempy] != ' ' && (int) tempx >= 0
		&& (int)(tempx + 0.2) <= data->map->max_height
		&& (int) tempy >= 0
		&& (int)(tempy + 0.2) < (int) ft_strlen(map[(int) tempx]) - 1);
}

bool	ft_ver_col(char **map, double tempx, double tempy, t_data *data)
{
	t_door	*tmp;

	tmp = data->head_door;
	if (map[(int)(tempx - 0.2)][(int)(tempy - 0.2)] == 'H'
		|| map[(int)(tempx + 0.2)][(int)(tempy + 0.2)] == 'H'
		|| map[(int)tempx][(int)tempy] == 'H')
	{
		while (tmp)
		{
			if ((tmp->x_pos == (int)(tempx + 0.2)
				&& tmp->y_pos == (int)(tempy + 0.2))
				|| (tmp->x_pos == (int)(tempx + 0.2)
					&& tmp->y_pos == (int)(tempy + 0.2))
				|| (tmp->x_pos == (int)(tempx)
					&& tmp->y_pos == (int)(tempy)))
				return (tmp->pos == 1);
			tmp = tmp->next;
		}
	}
	return (ft_ver_col_return(map, tempx, tempy, data));
}
