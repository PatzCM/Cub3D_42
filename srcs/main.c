#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data || ac != 2)
		return (write(1, "Error\n", 6), 1);
	init_data(data);
	parse_textures(data, av[1]);
	printf("NO: %s\n", data->map_data.NO);
	printf("SO: %s\n", data->map_data.SO);
	printf("WE: %s\n", data->map_data.WE);
	printf("EA: %s\n", data->map_data.EA);
	printf("F: %s\n", data->map_data.F);
	printf("C: %s\n", data->map_data.C);
	rgb_int(data);
	printf("Color F: %d\n", data->map_data.color_f);
	printf("Color C: %d\n", data->map_data.color_c);
	parse_cub_file(".cub", av[1]);
	/*copy_map(data, av[1]);*/
	/*if (parse_map(data) == false)*/
	/*	return (write(1, "Error\n", 6), 1);*/

}
