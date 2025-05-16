/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/16 14:17:10 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	raycaster(t_data *data)
{
	int x;

	x = -1;
	while (1)
	{
		while (++x < screenWidth)
		{
			calculate_ray_Dir(data);
			calculate_next(data);
			calculate_side(data);
			check_walls(data);
		}
	}
}