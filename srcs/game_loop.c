/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/16 18:24:20 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	raycaster(t_data *data, int worldMap[24][24])
{
	int x;

	x = -1;
	while (++x < screenWidth)
	{
		calculate_ray_Dir(data, x);
		calculate_next(data);
		calculate_side(data);
		check_walls(data, worldMap);
		calculate_perpendicular(data);
		calculate_lines(data);
		draw_line(data, x, worldMap);
	}
}
