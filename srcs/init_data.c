#include "../incs/cub3d.h"

void	init_data(t_data *data)
{
	data->player_count = 0;
	data->map.max_width = 0;
	data->map.max_height = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
}
