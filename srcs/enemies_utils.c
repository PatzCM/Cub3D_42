/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:14:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/06 12:24:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void order_enemies(t_data *data)
{
	t_enemy *current;
	t_enemy *tmp;

	current = data->enemies;
	tmp = NULL;
	while(current->next)
	{
		if (current->distance < current->next->distance)
		{
			tmp = current;
			current = current->next;
			tmp->next = current->next;
			current->prev = tmp->prev;
			tmp->prev = current;
			if (current->next)
				current->next->prev = tmp;
			current->next = tmp;
			if (current->prev)
				current->prev->next = current;
			current = data->enemies;
		}
		else
			current = current->next;
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
	printf("enemy count: %i\n", count);
}

void	take_enemy_out(t_data *data, int enemy_dead)
{
	t_enemy *current;

	current = data->enemies;
	while(current != NULL)
	{
		if (current->id == enemy_dead)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			data->worldMap[(int)(current->pos_x)][(int)(current->pos_y)] = 0;
			free(current);
			return ;
		}
		current = current->next;
	}
}