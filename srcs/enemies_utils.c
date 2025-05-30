/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:14:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/30 15:10:50 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void order_enemies(t_data *data)
{
	t_enemy *tmp;
	t_enemy *first_node;

	tmp = NULL;
	first_node = data->enemies;
	while(data->enemies->next != NULL)
	{
		if (data->enemies->distance < data->enemies->next->distance)
		{
			tmp = data->enemies->next;
			data->enemies->next = tmp->next;
			tmp->next = data->enemies;
			data->enemies = first_node;
		}
		else
			data->enemies = data->enemies->next;
	}	
}

void	enemy_count(t_data *data)
{
	int i;
	int	j;
	int count;

	i = -1;
	j = -1;
	count = 0;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (data->worldMap[i][j] == 2)
				count++;	
		}
	}
	data->numb_of_enemies = count;
}