/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:27:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/21 17:53:41 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_exit(data);
	else if (keycode == XK_w || keycode == XK_Up)
		data->keys[0] = true;
	else if (keycode == XK_s || keycode == XK_Down)
		data->keys[1] = true;
	else if (keycode == XK_a || keycode == XK_Left)
		data->keys[2] = true;
	else if (keycode == XK_d || keycode == XK_Right)
		data->keys[3] = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w || keycode == XK_Up)
		data->keys[0] = false;
	else if (keycode == XK_s || keycode == XK_Down)
		data->keys[1] = false;
	else if (keycode == XK_a || keycode == XK_Left)
		data->keys[2] = false;
	else if (keycode == XK_d || keycode == XK_Right)
		data->keys[3] = false;
	return (0);
}

void	handle_inputs(t_data *data)
{
	double movespeed = 5.0 * data->delta_time;
	double rotspeed = 3.0 * data->delta_time;
	double	old_Dir;
	double	old_PlaneX;
	
	if (data->keys[0])
	{
		if (data->worldMap[(int)(data->pos_X + data->dir_vec_X * movespeed)][(int)data->pos_Y] == 0)
			data->pos_X += data->dir_vec_X * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y + data->dir_vec_Y * movespeed)] == 0)
			data->pos_Y += data->dir_vec_Y * movespeed;
	}
	if (data->keys[1])
	{
		if (data->worldMap[(int)(data->pos_X - data->dir_vec_X * movespeed)][(int)data->pos_Y] == 0)
			data->pos_X += -data->dir_vec_X * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y - data->dir_vec_Y * movespeed)] == 0)
			data->pos_Y += -data->dir_vec_Y * movespeed;
	}
	if(data->keys[2])
	{
		old_Dir = data->dir_vec_X;
		data->dir_vec_X = data->dir_vec_X * cos(rotspeed) - data->dir_vec_Y * sin(rotspeed);
		data->dir_vec_Y = old_Dir * sin(rotspeed) + data->dir_vec_Y * cos(rotspeed);
		old_PlaneX = data->plane_X;
		data->plane_X = data->plane_X * cos(rotspeed) - data->plane_Y * sin(rotspeed);
		data->plane_Y = old_PlaneX * sin(rotspeed) + data->plane_Y * cos(rotspeed);
	}
	if(data->keys[3])
	{
		old_Dir = data->dir_vec_X;
		data->dir_vec_X = data->dir_vec_X * cos(-rotspeed) - data->dir_vec_Y * sin(-rotspeed);
		data->dir_vec_Y = old_Dir * sin(-rotspeed) + data->dir_vec_Y * cos(-rotspeed);
		old_PlaneX = data->plane_X;
		data->plane_X = data->plane_X * cos(-rotspeed) - data->plane_Y * sin(-rotspeed);
		data->plane_Y = old_PlaneX * sin(-rotspeed) + data->plane_Y * cos(rotspeed);
	}
}