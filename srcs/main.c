#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data || ac != 2)
		return (write(1, "Error\n", 6), 1);
	init_data(data);
	parse_cub_file(".cub", av[1]);
	parse_textures(data, av[1]);
	rgb_int(data);
	trim_and_check(data);
	copy_map(data, av[1]);
	/*if (parse_map(data) == false)*/
	/*	return (write(1, "Error\n", 6), 1);*/

}
