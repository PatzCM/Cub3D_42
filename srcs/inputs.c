/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:27:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/16 12:49:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static int	keystroke(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_exit(data);
	return (0);
}

void	handle_inputs(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, keystroke, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
}